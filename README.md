# ESP32 WiFi Jammer Projesi

Bu proje, ESP32 mikrodenetleyici kullanarak belirli bir WiFi ağına bağlı cihazları tespit edip, onlara sahte **Deauthentication (deauth)** paketleri göndererek bağlantılarını koparmayı amaçlar. Bu yöntemle, hedef WiFi ağına bağlı cihazların bağlantısı engellenir ve ağ kullanılamaz hale getirilir.

---

## Proje Amacı

- Hedef Access Point (AP) ve ona bağlı cihazların MAC adreslerini otomatik olarak tespit etmek,
- Tespit edilen cihazlara belirli aralıklarla sahte Deauthentication paketleri göndererek onları WiFi bağlantısından koparmak,
- Böylece hedef WiFi ağını geçici olarak devre dışı bırakmak (Jamming/DoS etkisi yaratmak).

---

## Nasıl Çalışır?

1. **Hedef AP'nin MAC adresi** önceden bilinmeli ve koda girilmelidir.  
   Windows için MAC adresini öğrenmek için Komut İstemi'nde (CMD) şu komut kullanılabilir:
   ```bash
   ipconfig /all
