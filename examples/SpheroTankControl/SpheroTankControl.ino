/************************************************
 Written by Cruz Monrreal II
 Created on 08-19-2012
 Modified on 11-11-2012
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Sphero-Library
************************************************/

#include <Bluetooth.h>
#include <Sphero.h>
#include <SabertoothSimplified.h>

Bluetooth bluetooth;
Sphero sphero;
SabertoothSimplified ST;

void setup() {
  Serial.begin(9600);
  ST.drive(0);
  ST.turn(0);
  
  delay(3000);
  
  // Connect to Sphero
  bluetooth.beginCMD();
  bluetooth.connect();
  bluetooth.endCMD();
  
  // Lock motors
  sphero.setStabilization(0);
  
  // Give user a chance to align w/ dot
  for(int i=0; i<10; i++){
    sphero.setBackLED(0xFF);
    delay(500);
    sphero.setBackLED(0x00);
    delay(500);
  }
  
  // Indicator LED
  sphero.setBackLED(0xFF);
  
  // Init Heading to 0
  sphero.setHeading(0x00);
  
  // Get Pitch @ 10Hz
  sphero.setStreamingData(10, 1, SPHERO_IMU_PITCH | SPHERO_IMU_YAW);
}

void loop() {  
  signed short pitch, yaw;
  sphero.readAsyncPacket();
  
  pitch = sphero.getData(0) << 8 | sphero.getData(1);
  yaw = sphero.getData(2) << 8 | sphero.getData(3);
  
  if (yaw < -70 && yaw > -140){
    ST.turn(50);
  }else if (yaw > 70 && yaw < 140){
    ST.turn(-50);
  }else if (pitch < -50){
    ST.drive(-100);
    //ST.turn(0);
  }else if (pitch > 50){
    ST.drive(100);
  }else{
    ST.drive(0);
    ST.turn(0);
  }
}