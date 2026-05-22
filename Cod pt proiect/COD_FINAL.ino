#include <Servo.h>

// Pini Motoare
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

//  Periferice
const int servoPin      = 8;
const int buzzerFata    = 9;  
const int buzzerStanga  = 13; 
const int buzzerDreapta = 12; 

const int trigFata    = 10;
const int echoFata    = 11;
const int trigStanga  = 20; 
const int echoStanga  = 21; 
const int trigDreapta = 3; 
const int echoDreapta = 2; 

Servo myservo;

unsigned long startTime;
const unsigned long limitTime = 120000; 

int angle = 90;
int step = 3;
bool goingForward = true;

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(trigFata, OUTPUT);    pinMode(echoFata, INPUT);
  pinMode(trigStanga, OUTPUT);  pinMode(echoStanga, INPUT);
  pinMode(trigDreapta, OUTPUT); pinMode(echoDreapta, INPUT);
  pinMode(buzzerFata, OUTPUT);
  pinMode(buzzerStanga, OUTPUT);
  pinMode(buzzerDreapta, OUTPUT);
  
  digitalWrite(buzzerFata, HIGH); 
  myservo.attach(servoPin);
  myservo.write(angle);
  startTime = millis(); 
}

void loop() {
  // lim-timp
  if (millis() - startTime > limitTime) {
    motorStop();
    digitalWrite(buzzerFata, HIGH);
    noTone(buzzerStanga);
    noTone(buzzerDreapta);
    while(true); 
  }
//distanta
  float distFata = readDistance(trigFata, echoFata);
  float distStanga = readDistance(trigStanga, echoStanga);
  float distDreapta = readDistance(trigDreapta, echoDreapta);

  // buzz lat
  if (distStanga < 30.0 && distStanga > 1.0) {
    tone(buzzerStanga, 800); 
  } else {
    noTone(buzzerStanga);
  }

  if (distDreapta < 30.0 && distDreapta > 1.0) {
    tone(buzzerDreapta, 800); 
  } else {
    noTone(buzzerDreapta);
  }

  // control
  if (distFata > 1.0 && distFata < 35.0) { 
    motorStop();
    digitalWrite(buzzerFata, LOW); 

    if (distStanga > 25.0) { 
      while (readDistance(trigFata, echoFata) < 40.0) {
        if (millis() - startTime > limitTime) break; 
        turnLeft(); 
        delay(50);
      }
    } 
    else if (distDreapta > 25.0) {
      while (readDistance(trigFata, echoFata) < 40.0) {
        if (millis() - startTime > limitTime) break;
        turnRight();
        delay(50);
      }
    }
    digitalWrite(buzzerFata, HIGH); 
  } 
  else {
    forward();
    
    // scan
    myservo.write(angle);
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
    delay(25); // delay
  }
}

float readDistance(int t, int e) {
  digitalWrite(t, LOW);
  delayMicroseconds(2);
  digitalWrite(t, HIGH);
  delayMicroseconds(10);
  digitalWrite(t, LOW);
  long duration = pulseIn(e, HIGH, 25000); 
  if (duration == 0) return 999.0;
  return duration * 0.034 / 2.0;
}

void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  
}

void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  
  digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW); 
}

void motorStop() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}
