/* Measure data from MPU - accelerometer/gyro and prints the roll, pitch, yaw and distance data from ultrasonic sensor, 
buzzez if distance less than 10 cm */

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>


// ... (include statements remain unchanged)

#define TRIG_PIN 2
#define ECHO_PIN 4
#define BUZZER_PIN 5

MPU6050 mpu;

void setup() {
  Serial.begin(38400);
  Wire.begin();
  
  mpu.initialize();
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  float pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
  float roll = atan2(ay, az) * 180.0 / PI;

  Serial.print("Gyro: ");
  Serial.print(gx); Serial.print(", ");
  Serial.print(gy); Serial.print(", ");
  Serial.print(gz); Serial.print(" | ");
  Serial.print("Pitch: ");
  Serial.print(pitch); Serial.print(" | ");
  Serial.print("Roll: ");
  Serial.print(roll); Serial.print(" | ");

  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= 10 || abs(gy) > 1500) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(500);
}
