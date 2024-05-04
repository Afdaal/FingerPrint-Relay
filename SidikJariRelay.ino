#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

#define RELAY_PIN 8

void setup() {
  Serial.begin(9600);
  finger.begin(57600);
  delay(5);
  
  if (!finger.verifyPassword()) {
    Serial.println("Gagal terhubung dengan sensor sidik jari");
    while (1) {
      delay(1);
    }
  }

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  
  Serial.println("Tempelkan jari Anda");
}

void loop() {
  int fingerprintID = getFingerPrint();

  if (fingerprintID != -1) {
    Serial.print("Sidik jari terdeteksi! ID: ");
    Serial.println(fingerprintID);
    
    if (fingerprintID == 1) {
      Serial.println("Sidik jari benar, relay aktif!");
      digitalWrite(RELAY_PIN, LOW);
      delay(3000);
      digitalWrite(RELAY_PIN, HIGH);
    } else {
      Serial.println("Sidik jari salah, relay tidak aktif");
    }
  }
  delay(50);  // Tambahkan sedikit jeda sebelum pemindaian berikutnya
}

int getFingerPrint() {
  int p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) return -1;

  // Sidik jari terdeteksi
  return finger.fingerID;
}
