/************************************************
 Written by Cruz Monrreal II
 Created on 06-26-2012
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Bluetooth-Library
************************************************/

// 
// Includes
// 

#include <stdint.h>
#include <Arduino.h>
#include "Sphero.h"

//
// Constructor
//
Sphero::Sphero(SoftwareSerial &serial){
    bluetooth = &serial;
}

//
// Destructor
//
Sphero::~Sphero(){}


//uint8_t Sphero::boost(uint16_t heading, uint8_t duration);
uint8_t Sphero::roll(short heading, char speed){
    return sendSynchronousPacket(0x02, 0x30, 0x02, 0x05, speed, heading >> 8 , heading, 0xFF);
}
//uint8_t Sphero::stop();
uint8_t Sphero::setRGBColor(char red, char green, char blue){
    return sendSynchronousPacket(0x02, 0x20, 0x01, 0x05, red, green, blue, 0x00);
}
uint8_t Sphero::setBackLED(char intensity){
    return sendSynchronousPacket(0x02, 0x21, 0x04, 0x02, intensity);
}
//uint8_t Sphero::setRotationRate(uint8_t rate);
uint8_t Sphero::rotateHeadingBy(short heading){
    return sendSynchronousPacket(0x02, 0x01, 0x03, 0x03, heading >> 8 , heading);
}
//uint8_t Sphero::setMotionTimeout();
//uint8_t Sphero::setRawMotorValues(uint8_t l_mode, uint8_t r_mode, uint8_t l_pwr, uint8_t r_pwr);

uint8_t Sphero::sendSynchronousPacket(uint8_t DID, uint8_t CID, uint8_t SEQ, uint8_t DLEN, ...){
    uint16_t i=0;
    uint8_t sum=0, tmp;
    va_list args;
    
    bluetooth->write(uint8_t(0xFF));
    bluetooth->write(uint8_t(0xFF));
    bluetooth->write(uint8_t(DID));
    bluetooth->write(uint8_t(CID));
    bluetooth->write(uint8_t(SEQ));
    bluetooth->write(uint8_t(DLEN));
    
    sum += DID + CID + SEQ + DLEN;
    
    va_start(args, DLEN);
    for(; i<DLEN-1; i++){
        tmp = va_arg(args, int);
        bluetooth->write(uint8_t(tmp));
        sum += tmp;
    }
    va_end(args);
    //delay(1);
    bluetooth->write(uint8_t(~sum));
    //bluetooth->print('\n');
    
    return readResponsePacket();
}

uint8_t Sphero::readResponsePacket(){
    //while(bluetooth->available());
    
    return 0;
}
