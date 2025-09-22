/**
 * @file Arduino_NRF24L01_Code.ino
 * @brief Demonstrates wireless data transmission using an NRF24L01 module.
 * @details This sketch configures an Arduino as a transmitter using the RF24 library.
 *          It initializes the NRF24L01 module, opens a writing pipe to a specific
 *          address, and repeatedly sends a sample data string. This code serves as the
 *          foundational logic for the wireless communication component of the CattleSense node.
 * 
 * @hardware Arduino UNO/Nano, NRF24L01 Transceiver Module
 * @dependencies RF24 library, SPI library
 */

#include <SPI.h>
#include <RF24.h>

// --- Pin Definitions & Global Objects ---

// Define the CE (Chip Enable) and CSN (Chip Select Not) pins for the NRF24L01 module
const int NRF_CE_PIN = 9;
const int NRF_CSN_PIN = 10;

// A constant for the 5-byte pipe address. This must match the receiver's address.
const byte PIPE_ADDRESS[6] = "00001"; 

// Create an RF24 object, specifying the CE and CSN pins
RF24 radio(NRF_CE_PIN, NRF_CSN_PIN);


/**
 * @brief Initializes serial communication and the NRF24L01 radio module.
 */
void setup() {
  Serial.begin(9600);
  
  // Initialize the radio module
  if (!radio.begin()) {
    Serial.println("Radio hardware is not responding!");
    while (1) {} // Halt execution if the module is not found
  }
  
  // Set the radio to be a transmitter by opening a writing pipe
  // The address must be a 5-byte identifier.
  radio.openWritingPipe(PIPE_ADDRESS);
  
  // Set the power amplifier level. RF24_PA_MIN is the lowest, RF24_PA_MAX is the highest.
  radio.setPALevel(RF24_PA_MIN);
  
  // Stop listening, as this is a dedicated transmitter
  radio.stopListening();
}


/**
 * @brief Main loop: sends a sample data payload every second.
 */
void loop() {
  // In a real application, this string would be replaced with actual sensor data
  // (e.g., a formatted string like "LAT:12.34,LON:56.78,BPM:75")
  const char text[] = "Hello from CattleSense Node!";
  
  // Send the data. The `write()` function blocks until the transmission is complete.
  bool success = radio.write(&text, sizeof(text));
  
  // Check if the transmission was successful and print the result
  if (success) {
    Serial.println("Data sent successfully.");
  } else {
    Serial.println("Data transmission failed.");
  }

  delay(1000);
}
