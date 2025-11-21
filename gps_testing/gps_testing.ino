/* GPS and prints crrent coordinates */

#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Choose the pins for your GPS module
SoftwareSerial gpsSerial(0, 1);  // RX, TX

TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
}

void loop() {
  // Read data from the GPS module
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        // Display latitude and longitude
        Serial.print("Latitude: ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Longitude: ");
        Serial.println(gps.location.lng(), 6);
      } else {
        Serial.println("GPS data not valid");
      }
    }
  }
}
