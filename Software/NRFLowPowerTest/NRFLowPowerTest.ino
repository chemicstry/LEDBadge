#include <SPI.h>
#include "LowPower.h"
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

const uint64_t pipe = 0xABCDEFABCDLL;

RF24 radio(9,10);

void setup() {
  Serial.begin(115200);
  Serial.println("NRF Low Power Receiver");
  printf_begin();

  radio.begin();
  radio.setAutoAck(false);
  radio.openReadingPipe(1,pipe);
  radio.startListening();                 // Start listening
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
}

#define RX_TIME 5000
unsigned long start;

void loop() {
  // Listen for short amount of time
  start = micros();
  while (micros() < start + RX_TIME)
  {
    if (radio.available())
    {
      byte data;
      radio.read(&data, sizeof(data));
      Serial.print("Got: ");
      Serial.println(data);
    }
  }
  
  // Power off
  radio.stopListening();
  radio.powerDown();
  Serial.println("Sleeping");
  Serial.flush();
  LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);  
  Serial.println("Waking up");
  radio.startListening();
}
