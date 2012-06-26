/************************************************
 Written by Cruz Monrreal II
 Created on 06-26-2012
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Bluetooth-Library
************************************************/

#include <SoftwareSerial.h>
#include <Sphero.h>

SoftwareSerial bluetooth(2,3);
Sphero sphero(bluetooth);

void setup() {
  Serial.begin(115200);
  bluetooth.begin(9600);
  
  // Turn on Back LED
  sphero.setBackLED(0xFF);
}

// ♫♫♫ You Spin Me Right Round ♫♫♫
void loop() {
  sphero.rotateHeadingBy(90);
}
