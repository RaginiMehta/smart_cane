/* Measure data from MPU - accelerometer/gyro and prints the gyro and accleration and distance data from ultrasonic sensor, 
buzzez if distance less than 50 cm */

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

#define TRIG_PIN 2
#define ECHO_PIN 4
#define BUZZER_PIN 5  // Change this to the pin where your buzzer is connected

MPU6050 mpu;

void setup() {
  Serial.begin(38400);
  Wire.begin();
  
  // Initialize MPU6050
  mpu.initialize();
  
  // Initialize Ultrasonic Sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Read MPU6050 data
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Print MPU6050 data
  Serial.print("Accel: ");
  Serial.print(ax); Serial.print(", ");
  Serial.print(ay); Serial.print(", ");
  Serial.print(az); Serial.print(" | ");
  Serial.print("Gyro: ");
  Serial.print(gx); Serial.print(", ");
  Serial.print(gy); Serial.print(", ");
  Serial.print(gz); Serial.print(" | ");

  // Read Ultrasonic Sensor data
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;  // Convert the time into distance in centimeters
  
  // Print Ultrasonic Sensor data
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if an object is detected at 50 cm
  if (distance <= 50) {
    // Buzz the buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);  // Adjust as needed for the buzzer sound duration
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(500);  // Adjust delay as needed
}
