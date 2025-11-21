/*buzzes based on distance, 
detects vibration using vibration sensor,
sends collisoin over blouetooth, bluetooth integration required */

#include <SoftwareSerial.h>

#define TRIG_PIN 2
#define ECHO_PIN 4
#define BUZZER_PIN 5
const int vibrationPin = 6;  // Connect SW-420 signal pin to digital pin 2
int collisionThreshold = 100000;

SoftwareSerial bluetoothSerial(10, 11);  // RX, TX for Bluetooth module

void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);  // Initialize Bluetooth serial communication
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(vibrationPin, INPUT);

  // Initial buzzer test
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
  delay(1000);  // Wait for a moment before starting the main loop
}

void loop() {
  long duration, distance;

  // Trigger ultrasonic sensor to measure distance
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;  // Convert the duration to centimeters

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Determine the buzzer behavior based on distance
  if (distance <= 70) {
    toneBuzzer(150);  // Beep with a 150ms delay
  }
  if (distance <= 50) {
    toneBuzzer(100);   // Beep with a 100ms delay
  }
  if (distance <= 15) {
    digitalWrite(BUZZER_PIN, HIGH); 
  }
  else digitalWrite(BUZZER_PIN, LOW);
  
  int vibrationValue = digitalRead(vibrationPin);

  // Send vibration value over Bluetooth
  bluetoothSerial.print("Vibration: ");
  bluetoothSerial.println(vibrationValue);

  if (vibrationValue == HIGH) {
    Serial.println("Collision detected!");
    // Add any additional actions or logic you want to perform on collision
    digitalWrite(BUZZER_PIN, HIGH);
    delay(2000);
    digitalWrite(BUZZER_PIN, LOW);

    // Delay to avoid multiple detections for a single collision event
    delay(2000);
  }

  delay(500);  // Adjust the delay based on your preferences
}

void toneBuzzer(int delayTime) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(delayTime);
  digitalWrite(BUZZER_PIN, LOW);
  delay(delayTime);
}