#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 10); // RX, TX

int i;
int dat[32] = {0};
unsigned long previousMillis = 0;
const long interval = 500; // Interval for processing data in milliseconds

void setup() {
  Serial.begin(9600);
  mySerial.begin(115200);
}

void processTofData() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    for (i = 0; i < 16; i++) {
      if (dat[i] == 0x57 && dat[i + 1] == 0 && dat[i + 2] == 0xff && dat[i + 3] == 0) {
        if (dat[i + 12] + dat[i + 13] * 255 == 0) {
          Serial.println("Out of range!");
        } else {
          int status = dat[i + 11];
          int strength = dat[i + 12] + dat[i + 13] * 255;
          int distance = dat[i + 8] + dat[i + 9] * 255;

          Serial.print("Status = ");
          Serial.print(status);
          Serial.print("  Strength = ");
          Serial.print(strength);
          Serial.print("  Distance = ");
          Serial.print(distance);
          Serial.println(" mm");
        }
        break;
      }
    }
  }
}

void loop() {
  if (mySerial.available() >= 32) {
    for (i = 0; i < 32; i++) {
      dat[i] = mySerial.read();
    }

    processTofData();
  }
}
