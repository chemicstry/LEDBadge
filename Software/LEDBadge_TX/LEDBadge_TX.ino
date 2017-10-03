#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

const uint64_t pipe = 0xABCDEFABCDLL;

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 
RF24 radio(9,10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("NRF Transmitter");
  printf_begin();

  radio.begin();
  radio.setAutoAck(false);
  radio.openWritingPipe(pipe);
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
}

byte data = 0xAB;

void loop()
{
  radio.write(&data, sizeof(data));
  delayMicroseconds(1000);
}

