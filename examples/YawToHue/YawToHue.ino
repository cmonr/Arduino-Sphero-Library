/************************************************
 Written by Cruz Monrreal II
 Created on 10-20-2012
 
 Initial HSV-to-RGB code from
  http://splinter.com.au/blog/?p=29
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Sphero-Library
************************************************/

#include <Sphero.h>
Sphero sphero;

void setup() {
  // Turn on Back LED
  sphero.setBackLED(0xFF);
  
  // Turn off Stabilization
  sphero.setStabilization(0);
  
  // Init current heading to 0
  sphero.setHeading(0x00);
  
  // Setup streaming data of Yaw angle
  sphero.setStreamingData(10, 1, SPHERO_IMU_YAW);
}

void loop(){
  // Busy-wait until Async packet is received
  sphero.readAsyncPacket();
  
  // Convert Angle to RGB and set Sphero's Color accordingly
  setLedColorHSV((signed short)(sphero.getData(0) << 8 | sphero.getData(1)) + 180);
}

void setLedColorHSV(int h) {
  float r,g,b;
  r=g=b=0;

  float hf=h/60.0;

  char i=(char) floor(h/60.0);
  float f = h/60.0 - i;
  float qv = 1 - f;
  float tv = 1 - (1 - f);

  switch (i){
    case 0: r = 1;  g = tv; b = 0;  break;
    case 1: r = qv; g = 1;  b = 0;  break;
    case 2: r = 0;  g = 1;  b = tv; break;
    case 3: r = 0;  g = qv; b = 1;  break;
    case 4: r = tv; g = 0;  b = 1;  break;
    case 5: r = 1;  g = 0;  b = qv; break;
  }

  sphero.setRGBColor(r*255, g*255, b*255);
}
