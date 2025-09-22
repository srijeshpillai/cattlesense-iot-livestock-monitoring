/**
 * @file Arduino_Heartbeat_Code.ino
 * @brief Reads analog data from a pulse sensor and converts it to BPM.
 * @details This sketch reads the raw analog value from a heartbeat sensor connected
 *          to pin A0. While this example prints the raw value, a complete implementation
 *          would use a dedicated library (like "PulseSensor Playground") to process this
 *          signal and calculate an accurate Beats Per Minute (BPM) value. This serves
 *          as the physiological monitoring component of the CattleSense IoT node.
 * 
 * @hardware Arduino UNO/Nano, Pulse Sensor
 */

// --- Pin Definitions & Constants ---
const int HEARTBEAT_SENSOR_PIN = A0; // Analog pin for the pulse sensor


/**
 * @brief Initializes the hardware serial for debugging output.
 */
void setup() {
  // Start serial communication for printing values to the Serial Monitor
  Serial.begin(9600);
}


/**
 * @brief Main loop: reads sensor data, prints it, and waits.
 */
void loop() {
  // Read the raw analog value from the heartbeat sensor (typically 0-1023)
  int rawHeartbeatValue = analogRead(HEARTBEAT_SENSOR_PIN);

  // Print the raw sensor data for debugging and verification
  // Note: A full implementation would process this into BPM before transmission.
  Serial.print("Raw Heartbeat Sensor Value: ");
  Serial.println(rawHeartbeatValue);

  // A short delay to make the serial output readable and to mimic a realistic sampling rate
  delay(1000); 
}
