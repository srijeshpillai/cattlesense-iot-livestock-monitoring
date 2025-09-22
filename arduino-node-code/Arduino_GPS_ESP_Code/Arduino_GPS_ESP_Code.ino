/**
 * @file Arduino_GPS_ESP_Code.ino
 * @brief Reads and parses GPS data from a NEO-6M module using TinyGPS++.
 * @details This sketch initializes a software serial connection to a GPS module,
 *          continuously reads NMEA sentences, and prints valid latitude and
 *          longitude coordinates to the serial monitor for debugging. It serves
 *          as the GPS data acquisition node in the CattleSense project.
 *
 * @hardware ESP8266/NodeMCU, NEO-6M GPS Module
 * @dependencies TinyGPS++ library, SoftwareSerial library
 */

#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// --- Pin Definitions & Global Objects ---
const int GPS_RX_PIN = 14; // NodeMCU D5 pin, connected to GPS TX
const int GPS_TX_PIN = 12; // NodeMCU D6 pin, connected to GPS RX

// Software serial for communication with the GPS module
SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);

// TinyGPS++ object to handle NMEA sentence parsing
TinyGPSPlus gps;


/**
 * @brief Initializes serial communication channels.
 */
void setup() {
  // Start the hardware serial for debugging output to the computer's Serial Monitor
  Serial.begin(9600);
  
  // Start the software serial to communicate with the GPS module
  gpsSerial.begin(9600);
}


/**
 * @brief Main loop: continuously reads and processes available GPS data.
 */
void loop() {
  // Process all available characters from the GPS module
  while (gpsSerial.available() > 0) {
    // Feed the data to the TinyGPS++ parser. The `encode()` method returns true
    // when a complete, valid NMEA sentence has been processed.
    if (gps.encode(gpsSerial.read())) {
      
      // After a sentence is parsed, check if the location data is valid
      if (gps.location.isValid()) {
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();

        // Print coordinates to the serial monitor for verification
        printCoordinates(latitude, longitude);

        // --- WIRELESS TRANSMISSION PLACEHOLDER ---
        // In the complete CattleSense system, this is where the coordinates would be sent
        // wirelessly to the central aggregator (Raspberry Pi) using a module
        // like an NRF24L01 or through the NodeMCU's built-in WiFi.
      }
    }
  }
}


/**
 * @brief Helper function to print latitude and longitude to the Serial Monitor.
 * @param latitude The latitude value.
 * @param longitude The longitude value.
 */
void printCoordinates(float latitude, float longitude) {
  Serial.print("Latitude: ");
  Serial.println(latitude, 6); // Using 6 decimal places for standard GPS precision
  
  Serial.print("Longitude: ");
  Serial.println(longitude, 6);
  
  Serial.println(); // Add a blank line for cleaner, more readable output
}
