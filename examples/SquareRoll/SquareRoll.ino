/************************************************
 Written by Cruz Monrreal II
 Created on 10-20-2012
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Bluetooth-Library
************************************************/

#include <Sphero.h>

Sphero sphero;

void setup() {
  // Turn on Back LED
  sphero.setBackLED(0xFF);
}

void loop() {
  sphero.roll(0, 0x80);
  delay(1000);
  
  sphero.stop(0, 0x00);
  delay(250);
  
  sphero.roll(90, 0x80);
  delay(1000);
  
  sphero.stop(0, 0x00);
  delay(250);
  
  sphero.roll(180, 0x80);
  delay(1000);
  
  sphero.stop(0, 0x00);
  delay(250);
  
  sphero.roll(270, 0x80);
  delay(1000);
  
  sphero.stop(0, 0x00);
  delay(250);
}