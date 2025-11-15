#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40);

unsigned int pos0 = 172;    // Pulso para 0 grados
unsigned int pos180 = 565;  // Pulso para 180 grados
unsigned int posCurrent = 90;

String inputString = "";

void setup() {
  servos.begin();
  servos.setPWMFreq(60);

  Serial.begin(115200);
  delay(1000);

  moverServo(90); // Posición inicial
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();

    if (c == '\n' || c == '\r') {
      inputString.trim();
      if (inputString == "A") {
        moverCabezaSuave();
      }
      inputString = "";
    } else {
      inputString += c;
    }
  }
}

void moverServo(int grado) {
  posCurrent = constrain(grado, 0, 180);
  int pulso = map(posCurrent, 0, 180, pos0, pos180);
  servos.setPWM(0, 0, pulso);
}

void moverCabezaSuave() {
  // Bajar de 90° a 50°
  for (int i = 90; i >= 50; i--) {
    moverServo(i);
    delay(10);
  }

  // Subir de 50° a 130°
  for (int i = 50; i <= 130; i++) {
    moverServo(i);
    delay(10);
  }

  // Volver de 130° a 90°
  for (int i = 130; i >= 90; i--) {
    moverServo(i);
    delay(10);
  }

}