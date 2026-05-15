// Mecanum robot cu Sensor Shield
// IN1=S5, IN2=S6, IN3=S10, IN4=S11

#define IN1 5
#define IN2 6
#define IN3 10
#define IN4 11

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Pornim robotul înainte
  forward();
  
  // Îl lăsăm să meargă timp de 5 secunde (5000 milisecunde)
  delay(5000);

  // Oprim motoarele
  stopMotors();
}

void loop() {
  // Lăsăm loop-ul gol pentru ca robotul să nu mai facă nimic după setup
}

// --- Funcțiile de mișcare rămân la fel ---

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
// Poți păstra restul funcțiilor (backward, strafe, etc.) mai jos, 
// chiar dacă nu le folosești acum.