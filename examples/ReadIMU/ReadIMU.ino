/************************************************
 Written by Cruz Monrreal II
 Created on 08-19-2012
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Bluetooth-Library
************************************************/

#include <Sphero.h>

Sphero sphero;

void setup() {
  Serial.begin(115200);
  delay(2000);
  sphero.setStabilization(0);
  sphero.setStreamingData(400, 1, 0x00040000);
  delay(2000);
}

void loop() {
  Serial.println("\n");
  
  sphero.readAsyncPacket();
}
