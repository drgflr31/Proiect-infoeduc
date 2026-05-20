#include <Servo.h>

Servo myservo;
int angle = 30;
int step = 1;
bool goingForward = true;

const int servoPin  = 6;
const int buzzerPin = 8;
const int trigPin   = 9;
const int echoPin   = 10;

long duration;
float distance_cm;

void setup() {
  myservo.attach(servoPin);
  myservo.write(angle);

  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

float readDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  float d = duration * 0.034 / 2.0;
  return d;
}

void loop() {
  myservo.write(angle);
  delay(15);

  distance_cm = readDistanceCM();

  Serial.print("Unghi: ");
  Serial.print(angle);
  Serial.print("  Distanta: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  if (distance_cm > 0 && distance_cm < 50) {
    tone(buzzerPin, 1000);
  } else {
    noTone(buzzerPin);
  }

  if (goingForward) {
    angle += step;
    if (angle >= 150) {
      angle = 150;
      goingForward = false;
    }
  } else {
    angle -= step;
    if (angle <= 30) {
      angle = 30;
      goingForward = true;
    }
  }
}
