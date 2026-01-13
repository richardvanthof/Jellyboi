// Ultrasonic Pins
const int trigPin = 7;
const int echoPin = 6;

// Motor Pins (L293D)
const int en1Pin = 10; 
const int in1Pin = 9;
const int in2Pin = 8;

//Light pins
const int led = 3;

const int jellySpeed = 255; // Your requested speed
  
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(en1Pin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

  pinMode(led, OUTPUT);
}

void loop() {
  // Distance Measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  if (distance > 0 && distance <= 100) {
    
    // --- JELLYFISH "UP" PHASE (Total ~1 second) ---
    // We do 2 quick pulses of: Push Forward -> Slight Back
    for (int i = 0; i < 2; i++) {
      // Push Up
      digitalWrite(in1Pin, HIGH);
      digitalWrite(in2Pin, LOW);
      analogWrite(en1Pin, jellySpeed);
      delay(200); 
      
      // Slight Down (The "Relax")
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, HIGH);
      analogWrite(en1Pin, 100); // Lower speed for the relax
      delay(150);

      digitalWrite(led, HIGH);
    }

    // --- RESET PHASE (Back down for 1 second) ---
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    analogWrite(en1Pin, jellySpeed);
    delay(1200);

    // --- STOP ---
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    analogWrite(en1Pin, 0);
    digitalWrite(led, LOW);
  }
  
  delay(50); 
}