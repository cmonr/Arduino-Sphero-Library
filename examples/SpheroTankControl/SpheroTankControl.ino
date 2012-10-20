/************************************************
 Written by Cruz Monrreal II
 Created on 08-19-2012
 Modified on 10-20-2012
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Sphero-Library
************************************************/

#include <Sphero.h>
#include <SabertoothSimplified.h>

Sphero sphero;
SabertoothSimplified ST;

void setup() {
  Serial.begin(9600);
  ST.drive(0);
  ST.turn(0);
  
  // Indicator LED
  sphero.setBackLED(0xFF);
  
  // Lock motors
  sphero.setStabilization(0);
  
  // Init Heading to 0
  sphero.setHeading(0x00);
  
  // Get Pitch @ 5Hz
  sphero.setStreamingData(10, 1, SPHERO_IMU_PITCH | SPHERO_IMU_YAW);
}

void loop() {  
  signed short pitch, yaw;
  sphero.readAsyncPacket();
  
  pitch = sphero.getData(0) << 8 | sphero.getData(1);
  yaw = sphero.getData(2) << 8 | sphero.getData(3);
  
  if (yaw < -70 && yaw > -140){
    ST.turn(-50);
  }else if (yaw > 70 && yaw < 140){
    ST.turn(50);
  }else if (pitch < -50){
    ST.drive(-50);
    //ST.turn(0);
  }else if (pitch > 50){
    ST.drive(50);
  }else{
    ST.drive(0);
    ST.turn(0);
  }
}
