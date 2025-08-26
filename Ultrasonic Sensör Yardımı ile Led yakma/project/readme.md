<img src="https://github.com/Muhammed-Turgut/imageRaw/blob/main/ultrasonik_sens%C3%B6r_projesi.png?raw=true" algn= "center">

# Arduino Uno Ultrasonic Sensör ve LED Projesi

Bu projede 3 kırmızı 3 sarı ve 3 yeşil ledi Ultrasoniksensörde analoıg okuma yapılarak ledleri yakıp söndürmeyi sağlıyoruz. 

---

## Proje Amacı

- Temel amaç Ultra sonik Sensörün çalışma manıtığını kavramak.


---

## Gerekli malzemeler

- 9 adet 220 ohm değerni sahip direnç.
- 3 adet kırmızı LED.
- 3 adet sarı LED.
- 3 adet yeşil LED
- 1 Arduino Uno.
- Jummper Kablo
- 1 adet Ultra sonik sensör (HC-SR04).



---

## Nasıl Çalışır?

1. **Potasyometreden** okuma yapılarak gelen değer üzerinden ledlerin belirli sırada yakıp söndürülmesi sağalanıyor.
  ```bash
   #define TRIG 9
   #define ECHO 10
   long sure;
   int mesafe;

   int leds[9] = {1, 2, 3, 4, 5, 6, 7, 8, 11};
  
   void setup() {
   for (int i = 0; i < 9; i++){
     pinMode(leds[i], OUTPUT);
   }

   pinMode(TRIG, OUTPUT);
   pinMode(ECHO, INPUT);
   Serial.begin(9600);
   }

   void loop() {
    // TRIG pinini temizle
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);

   // 10 µs tetik darbesi gönder
   digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // ECHO süresini ölç
  sure = pulseIn(ECHO, HIGH);

  // Mesafe hesapla (cm cinsinden)
  mesafe = sure * 0.034 / 2;

  // Önce tüm LED’leri söndür
  for (int i = 0; i < 9; i++) {
    digitalWrite(leds[i], LOW);
  }

  if (mesafe > 1 && mesafe < 10) {
    for (int i = 1; i <= 2; i++) {
      digitalWrite(leds[i], HIGH);
    }
  }

  else if (mesafe > 10 && mesafe < 20) {
    for (int i = 1; i <= 5; i++) {
      digitalWrite(leds[i], HIGH);
    }
  }

  else if (mesafe > 20 && mesafe < 30) {
    for (int i = 1; i <= 8; i++) {
      digitalWrite(leds[i], HIGH);
    }
  }

  else if (mesafe >= 40) {
    for (int i = 1; i < 11; i++) {
      digitalWrite(leds[i], HIGH);
    }
  }

  Serial.println(mesafe);
  delay(100);
}





