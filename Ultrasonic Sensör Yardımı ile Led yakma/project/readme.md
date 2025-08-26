<img src="https://github.com/Muhammed-Turgut/imageRaw/blob/main/Ardunio%20Potasyo%20metre%20ile%20led%20yakma%20projesi.png?raw=true" algn= "center">

# Arduino Uno Potasyometre ve LED Projesi

Bu projede 3 kırmızı 3 sarı ve 3 yeşil ledi Potasyometreden analoıg okuma yapılarak ledleri yakıp söndürmeyi sağlıyoruz. 

---

## Proje Amacı

- Temel amaç potasyometrenin çalışma manıtığını kavramak.


---

## Gerekli malzemeler

- 9 adet 220 ohm değerni sahip direnç.
- 3 adet kırmızı LED.
- 3 adet sarı LED.
- 3 adet yeşil LED
- 1 Arduino Uno.
- Jummper Kablo
- 1 adet Potasyometre (10k Ohm).



---

## Nasıl Çalışır?

1. **Potasyometreden** okuma yapılarak gelen değer üzerinden ledlerin belirli sırada yakıp söndürülmesi sağalanıyor.
   ```bash
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
<img src="https://github.com/Muhammed-Turgut/imageRaw/blob/main/ArdunioProjectImage.jpg" align="center" style="transform: rotate(90deg);">



