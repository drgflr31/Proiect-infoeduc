#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 8;

Servo myservo;

// --- SETĂRILE stas ---
float viteza = 0.05;      
int unghiMin = 20;        
int unghiMax = 160;       
int pauzaMasurare = 100; // Am mărit puțin pauza de printare ca să poată citi mai ușor
// ----------------------

float pos = unghiMin;
int directie = 1;
unsigned long timpAnterior = 0;

void setup() {
  myservo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // PORNIRE SERIALĂ
  Serial.begin(115200); 
  delay(1000); // Așteptăm o secundă să se stabilizeze conexiunea
  Serial.println("--- TEST RADAR PORNIRE ---");
}

void loop() {
  // 1. Mișcare motor
  pos += (viteza * directie);

  if (pos >= unghiMax) { directie = -1; }
  if (pos <= unghiMin) { directie = 1; }

  myservo.write((int)pos);

  // 2. Măsurare și afișare forțată
  unsigned long timpCurent = millis();
  if (timpCurent - timpAnterior >= pauzaMasurare) {
    timpAnterior = timpCurent;
    
    int dist = citesteDistanta();
    
    // Printăm brut pentru a vedea dacă ajung datele
    Serial.print("U:"); 
    Serial.print((int)pos);
    Serial.print(" | D:");
    Serial.print(distance);
    Serial.println(" cm");
  }
}

int citesteDistanta() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // pulseIn returnează 0 dacă nu primește semnal în 30ms
  long duration = pulseIn(echoPin, HIGH, 30000); 
  
  if (duration == 0) {
    return -1; // Semnalăm că senzorul nu primește ecou (eroare de cablaj)
  }
  
  return duration * 0.034 / 2;
}