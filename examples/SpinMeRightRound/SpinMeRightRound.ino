/************************************************
 Written by Cruz Monrreal II
 Created on 06-26-2012
 Modified on 10-20-2012
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Sphero-Library
************************************************/

#include <Sphero.h>
Sphero sphero;

void setup() {
  Serial.begin(115200);
  
  // Turn on Back LED
  sphero.setBackLED(0xFF);
  
  // Turn off Stabilization
  sphero.setStabilization(0);
    
  // ??? You Spin Me Right Round ???
  sphero.setMotorPowers(-80, 80);
}

void loop(){}
