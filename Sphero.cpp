/************************************************
 Written by Cruz Monrreal II
 Created on 06-26-2012
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Bluetooth-Library
************************************************/

#include <stdint.h>
#include <Arduino.h>
#include "Sphero.h"

Sphero::Sphero(SoftwareSerial &serial){
    bluetooth = &serial;
}

Sphero::~Sphero(){}

//uint8_t Sphero::boost(uint16_t heading, uint8_t duration);
void Sphero::roll(short heading, char speed){
    sendSynchronousPacket(0x02, 0x30, 0x02, 0x05, speed, heading >> 8 , heading, 0xFF);
}
//void Sphero::stop();
void Sphero::setRGBColor(char red, char green, char blue){
    sendSynchronousPacket(0x02, 0x20, 0x01, 0x05, red, green, blue, 0xFF);
}
void Sphero::getRGBColor(){
    sendSynchronousPacket(0x02, 0x22, 0x06, 0x01);
}
void Sphero::setBackLED(char intensity){
    sendSynchronousPacket(0x02, 0x21, 0x04, 0x02, intensity);
}
//void Sphero::setRotationRate(uint8_t rate);
void Sphero::rotateHeadingBy(short heading){
    sendSynchronousPacket(0x02, 0x01, 0x03, 0x03, heading >> 8 , heading);
}
//void Sphero::setMotionTimeout();
//void Sphero::setRawMotorValues(uint8_t l_mode, uint8_t r_mode, uint8_t l_pwr, uint8_t r_pwr);

void Sphero::sendSynchronousPacket(char DID, char CID, char SEQ, char DLEN, ...){
    short i=0;
    char sum=0, data;
    va_list args;
    
    // Write data
    bluetooth->write(char(0xFF));
    bluetooth->write(char(0xFF));
    bluetooth->write(char(DID));
    bluetooth->write(char(CID));
    bluetooth->write(char(SEQ));
    bluetooth->write(char(DLEN));
    
    // Calculate checksum
    sum += DID + CID + SEQ + DLEN;
    
    va_start(args, DLEN);
    for(; i<DLEN-1; i++){
        data = va_arg(args, int);
        bluetooth->write(char(data));
        sum += data;
    }
    va_end(args);
    
    // Write Checksum
    bluetooth->write(char(~sum));
    
    // Wait for response
    readResponsePacket();
}

void Sphero::readResponsePacket(){
    char ctr = 0;
    response = "";
    
    bluetooth->flush(); // Get rid of any stale data
    
    while(!bluetooth->available()){}        // Wait for response packet to begin
    
    response += char(bluetooth->read());    // Append first character
    
    while(ctr < 32  ){    // Arbritrary value
        if (bluetooth->available()){
            response += char(bluetooth->read());
            ctr = 0;
        }else{
            ctr++;
        }
    }
}

String Sphero::readRawResponse(){ return response; }

String Sphero::readResponseData(){
    if (response.charAt(4) > 1)
        return response.substring(5, 5 + (response.charAt(4)-1));
    return "";
}
  