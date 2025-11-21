/* beeps based on distance from obstacle, 
increases frequncy as shorter distances,
FIRST PROTOTYPE*/

#include <SoftwareSerial.h>

#define TRIG_PIN 2
#define ECHO_PIN 4
#define BUZZER_PIN 5
const int vibrationPin = 6;  // Connect SW-420 signal pin to digital pin 2
int collisionThreshold = 10000;
#define LDR_PIN A0
#define led_pin 8

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(vibrationPin, INPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(LDR_PIN, INPUT);

  
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
    toneBuzzer(150);  // Beep with a 100ms delay
  }
  if (distance <= 50) {
    toneBuzzer(100);   // Beep with a 50ms delay
  }
  if (distance <= 15) {
    digitalWrite(BUZZER_PIN, HIGH); 
   // Beep with a 20ms delay
  }
  else digitalWrite(BUZZER_PIN, LOW);
  int vibrationValue = digitalRead(vibrationPin);

  if (vibrationValue == HIGH) {
    Serial.println("Collision detected!");
    // Add any additional actions or logic you want to perform on collision
    digitalWrite(BUZZER_PIN, HIGH);
    delay(2000);
    digitalWrite(BUZZER_PIN, LOW);
    }

  //for light testing conditions
    int ldrValue = analogRead(LDR_PIN); // generating function for ldr pin input

      Serial.print("ldr");
      Serial.println(ldrValue);

    if (ldrValue < 200) {
      digitalWrite(led_pin, HIGH);
      Serial.println("LIght not detected, turing on precuation light");
      }
    else{
      digitalWrite(led_pin, LOW); 

    // Delay to avoid multiple detections for a single collision event
    delay(1000);
  }
  

  //delay(500);  // Adjust the delay based on your preferences
}

void toneBuzzer(int delayTime) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(delayTime);
  digitalWrite(BUZZER_PIN, LOW);
  delay(delayTime);
}