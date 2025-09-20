#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN pins

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(0x7878787878LL);  // Set the pipe address for communication
}

void loop() {
  String dataToSend = "Hello from Arduino!";
  
  radio.write(&dataToSend, sizeof(dataToSend));
  Serial.println("Data sent: " + dataToSend);

  delay(1000);
}
