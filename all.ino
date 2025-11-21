/* Measure data from MPU - accelerometer/gyro and checks fast movement,
uses gps for coordinates, 
and distance data from ultrasonic sensor, 
buzzez if distance less than 10 cm */

/* does not work yet, won't work for short distances hence it fails for this application*/

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <SoftwareSerial.h>

#define TRIG_PIN 2
#define ECHO_PIN 4
#define BUZZER_PIN 5  // Change this to the pin where your buzzer is connected

MPU6050 mpu;

// Define SoftwareSerial object for GPS module
SoftwareSerial gpsSerial(8, 9); // RX, TX

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

  // Initialize GPS module
  gpsSerial.begin(9600);
}

void loop() {
  // Read MPU6050 data
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Calculate pitch and roll angles
  float pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
  float roll = atan2(ay, az) * 180.0 / PI;

  // Print MPU6050 data including pitch and roll
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
  if (distance <= 50 || abs(gy) > 1500) {
    // Buzz the buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);  // Adjust as needed for the buzzer sound duration
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Read GPS data
  if (gpsSerial.available() > 0) {
    char gpsData = gpsSerial.read();

    // Process GPS data
    if (gpsData == '$') {
      // Start of a new NMEA sentence
      String sentence = "";
      
      // Read the complete sentence
      while (gpsSerial.available() > 0 && gpsData != '\n') {
        gpsData = gpsSerial.read();
        sentence += gpsData;
      }

      // Process the complete NMEA sentence
      processNMEA(sentence);
    }
  }

  delay(500);  // Adjust delay as needed
}

void processNMEA(String sentence) {
  // Your NMEA processing code here
  // Extract latitude and longitude, and use them as needed
  String fields[15];
  int index = 0;
  int startPos = 0;

  while (startPos < sentence.length() && index < 15) {
    int commaPos = sentence.indexOf(',', startPos);
    if (commaPos != -1) {
      fields[index++] = sentence.substring(startPos, commaPos);
      startPos = commaPos + 1;
    } else {
      fields[index++] = sentence.substring(startPos);
      break;
    }
  }

  // Now, you can access specific fields based on the NMEA sentence structure
  // For example, latitude and longitude
  String latitude = fields[2];
  String longitude = fields[4];

  // Convert latitude and longitude to float values if needed
  float lat = latitude.toFloat();
  float lon = longitude.toFloat();

  // Print or use lat, lon as needed
  Serial.print("Latitude: ");
  Serial.println(lat, 6);  // Print with 6 decimal places for better accuracy
  Serial.print("Longitude: ");
  Serial.println(lon, 6);

  // Generate Google Maps link
  String googleMapsLink = "https://www.google.com/maps?q=" + String(lat, 6) + "," + String(lon, 6);
  Serial.print("Google Maps Link: ");
  Serial.println(googleMapsLink);
}