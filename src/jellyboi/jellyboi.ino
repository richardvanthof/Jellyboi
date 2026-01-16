// =====================
// Ultrasonic Pins
// =====================
const int trigPin = 7;
const int echoPin = 6;

// =====================
// Motor Pins (L293D)
// =====================
const int en1Pin = 10;
const int in1Pin = 9;
const int in2Pin = 8;

// =====================
// Light Pin
// =====================
const int led = 3;

// =====================
// Settings
// =====================
const int minBrightness = 15;    // Dim glow when idle
const int triggerDistance = 80;  // cm
const int MOTOR_POWER = 255;     // motor PWM power

// Pulsing settings
const int pulsesPerCycle = 3;    // number of contractions per upward swim

// =====================
// Setup
// =====================
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(en1Pin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

  pinMode(led, OUTPUT);

  analogWrite(led, minBrightness);
}

// =====================
// Main Loop
// =====================
void loop() {
  int distance = checkDistance();

  if (distance <= triggerDistance) {
    jellySwim();    // swim only when someone is nearby
  } else {
    idleState();
  }
}

// =====================
// Jellyfish Swimming Motion
// =====================
void jellySwim() {

  for (int i = 0; i < pulsesPerCycle; i++) {

    // --- PULSE UP (contraction) ---
    motorUp();
    analogWrite(en1Pin, MOTOR_POWER);

    // LED fades in with contraction
    for (int b = minBrightness; b <= 255; b += 8) {
      analogWrite(led, b);
      delay(15);
    }

    delay(150); // hold peak contraction

    // --- RELAX SLIGHTLY (small downward movement) ---
    motorStop(); // rope drops slightly
    for (int b = 255; b >= minBrightness; b -= 6) { // LED fades out
      analogWrite(led, b);
      delay(20);
    }

    delay(200); // float / relaxation

  }

  motorStop();
  delay(400);
}

// =====================
// Motor Helpers
// =====================
void motorUp() {
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
}

void motorStop() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  analogWrite(en1Pin, 0);
}

// =====================
// Idle State
// =====================
void idleState() {
  motorStop();
  analogWrite(led, minBrightness);
  delay(100);
}

// =====================
// Distance Sensor
// =====================
int checkDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 20000); // 20ms timeout
  if (duration == 0) return 999;

  return duration * 0.034 / 2; // distance in cm
}