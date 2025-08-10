int leds[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // LED pinleri
int potPin = A0;
int potDeger = 0;

void setup() {
  for (int i = 0; i < 9; i++) {
    pinMode(leds[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  potDeger = analogRead(potPin); // 0-1023 arası değer
  Serial.println(potDeger);

  // Pot değerini 0-9 kademeye çevir
  int kademe = map(potDeger, 0, 1023, 0, 9);

  // Önce tüm LED'leri kapat
  for (int i = 0; i < 9; i++) {
    digitalWrite(leds[i], LOW);
  }

  // Kademeye kadar olan LED'leri yak
  for (int i = 0; i < kademe; i++) {
    digitalWrite(leds[i], HIGH);
  }

  delay(50); // Güncelleme hızı
}
