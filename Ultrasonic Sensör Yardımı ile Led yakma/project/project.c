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
