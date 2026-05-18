#include <Servo.h>

Servo myservo;

int angle = 30;        // unghiul de start (stânga)
int step = 1;          // cât se mișcă la fiecare pas
bool goingForward = true; // true = merge spre dreapta (unghi mai mare)

void setup() {
  myservo.attach(9);
  myservo.write(angle);
}

void loop() {
  myservo.write(angle);
  delay(15);           // controlează viteza mișcării

  if (goingForward) {
    angle += step;
    if (angle >= 150) {     // limita din dreapta (orizontala ta, de ex. 150°)
      angle = 150;
      goingForward = false; // schimbă direcția
    }
  } else {
    angle -= step;
    if (angle <= 30) {      // limita din stânga
      angle = 30;
      goingForward = true;  // schimbă direcția
    }
  }
}
