/*
 * Rui Santos 
 * Complete Project Details https://randomnerdtutorials.com
 */
 
#include <SoftwareSerial.h>

// The serial connection to the GPS module
SoftwareSerial ss(4, 3);

// Pin for the heartbeat sensor
const int heartbeatSensorPin = A0;

void setup(){
  Serial.begin(9600);
  ss.begin(9600);
}

void loop(){
  // Read data from GPS module
  while (ss.available() > 0){
    byte gpsData = ss.read();
    Serial.write(gpsData);
  }

  // Read data from heartbeat sensor
  int heartbeatValue = analogRead(heartbeatSensorPin);

  // Print heartbeat sensor data to Serial Monitor
  Serial.print("Heartbeat Sensor Value: ");
  Serial.println(heartbeatValue);

  // Add a delay to prevent too much output
  delay(1000);
}
