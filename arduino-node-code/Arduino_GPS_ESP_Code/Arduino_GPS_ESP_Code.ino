#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Define the RX and TX pins for the GPS module
const int gpsRxPin = 14; // D5 on NodeMCU
const int gpsTxPin = 12; // D6 on NodeMCU

SoftwareSerial gpsSerial(gpsRxPin, gpsTxPin); // Create a SoftwareSerial object

TinyGPSPlus gps; // Create a TinyGPS++ object

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  gpsSerial.begin(9600); // Initialize SoftwareSerial for GPS module
}

void printCoordinates(float latitude, float longitude) {
  Serial.print("Latitude: ");
  Serial.println(latitude, 4); // Adjust precision as needed
  Serial.print("Longitude: ");
  Serial.println(longitude, 4); // Adjust precision as needed
}

void loop() {
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        // Get latitude and longitude
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();

        // Print the coordinates to Serial for debugging
        printCoordinates(latitude, longitude);

        // Send the coordinates wirelessly to Raspberry Pi (implement your wireless communication here)
        // Example: You can use ESP8266 WiFi or any other wireless communication method
      }
    }
  }
}
