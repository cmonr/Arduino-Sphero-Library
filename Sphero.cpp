/************************************************
 Written by Cruz Monrreal II
 Created on 06-26-2012
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Bluetooth-Library
************************************************/

#include <stdint.h>
#include <Arduino.h>
#include "Sphero.h"

Sphero::Sphero(){
    //bluetooth = &serial;
    Serial1.begin(9600);
    mrsp = 0x00;
}

Sphero::~Sphero(){}

//uint8_t Sphero::boost(uint16_t heading, uint8_t duration);
char Sphero::roll(short heading, char speed){
    return sendSynchronousPacket(0x02, 0x30, 0x02, 0x05, speed, heading >> 8 , heading, 0xFF);
}
//void Sphero::stop();
char Sphero::setRGBColor(char red, char green, char blue){
    return sendSynchronousPacket(0x02, 0x20, 0x01, 0x05, red, green, blue, 0xFF);
}
char Sphero::getRGBColor(){
    return sendSynchronousPacket(0x02, 0x22, 0x06, 0x01);
}
char Sphero::setBackLED(char intensity){
    return sendSynchronousPacket(0x02, 0x21, 0x04, 0x02, intensity);
}
//void Sphero::setRotationRate(uint8_t rate);
char Sphero::rotateHeadingBy(short heading){
    return sendSynchronousPacket(0x02, 0x01, 0x03, 0x03, heading >> 8 , heading);
}
//void Sphero::setMotionTimeout();
//void Sphero::setRawMotorValues(uint8_t l_mode, uint8_t r_mode, uint8_t l_pwr, uint8_t r_pwr);

char Sphero::setStabilization(char enable){
    return sendSynchronousPacket(0x02, 0x02, 0x09, 0x02, enable==1);
}
    
char Sphero::setStreamingData(short sample_freq_divisor, short frames_per_packet, long int mask){
    return sendSynchronousPacket(0x02, 0x11, 0x07, 0x0A, (400/sample_freq_divisor) >> 8, (400/sample_freq_divisor), frames_per_packet >> 8, frames_per_packet, char(mask >> 24), char(mask >> 16), char(mask >> 8), char(mask), 5);
}

char Sphero::getOptionFlags(){
    return sendSynchronousPacket(0x02, 0x36, 0x08, 0x01);
}

char Sphero::sendSynchronousPacket(char DID, char CID, char SEQ, char DLEN, ...){
    short i=0;
    char sum=0, data;
    va_list args;
    
    // Flush pipe (just in case)
    //Serial1.flush();
    
    // Write data
    Serial1.write(char(0xFF));
    Serial1.write(char(0xFF));
    Serial1.write(char(DID));
    Serial1.write(char(CID));
    Serial1.write(char(SEQ));
    Serial1.write(char(DLEN));
    
    // Calculate checksum
    sum += DID + CID + SEQ + DLEN;
    
    va_start(args, DLEN);
    for(; i<DLEN-1; i++){
        data = va_arg(args, int);
        Serial1.write(data);
        
        Serial.print(String(data, HEX));
        Serial.print(" ");
        sum += data;
    }
    va_end(args);
    Serial.println();
    
    // Write Checksum
    Serial1.write(char(~sum));
    
    // Wait for Simple Response
    return readResponsePacket();
}

char Sphero::readResponsePacket(){
    int i, len;
    response = "";
    
    Serial1.flush(); // Get rid of any stale data
    
    Serial.println("Waiting for Simple Response");
    while(Serial1.available() < 5);
    
    Serial1.read();         // 0xFF
    Serial1.read();         // 0xFF
    Serial.print(" MRSP: ");
    mrsp = Serial1.read();  // MRSP
    Serial.print(String(mrsp, HEX));
    Serial.println();
    Serial.print(" SEQ: ");
    Serial.println(Serial1.read());     // SEQ
    Serial.print(" DLEN: ");
    len = Serial1.read();   // DLEN
    Serial.println(len, HEX);
    
    Serial.println(" Data:");
    Serial.print("  ");
    for(i=0; i<len-1; i++){
        char data; 
        while(!Serial1.available());
        
        data = char(Serial1.read());
        Serial.print(String(data, HEX));
        Serial.print(" ");
        response+=data;
    }    
    Serial.println();
    
    Serial.print(" Checksum: ");
    while(!Serial1.available());
    Serial.println(Serial1.read());     // CHK
    
    Serial1.flush();
    
    delay(10);
    
    return mrsp;
}

char Sphero::getMRSP(){
    return mrsp;
}

String Sphero::readAsyncPacket(){
    int i, len;
    response = "";
    
    Serial.println("Waiting for Async Packet");
    while(Serial1.available() < 5);
    
    Serial1.read();         // 0xFF
    Serial1.read();         // 0xFE
    Serial.print(" ID Code: ");
    Serial.println(Serial1.read());         // ID Code
    Serial.print(" DLEN: ");
    len = Serial1.read() << 8;  // DLEN-MSB
    len += Serial1.read();      // DLEN-LSB
    Serial.println(len);
    
    Serial.println(" Data:");
    for(i=0; i<len-1; i++){
        char data; 
        while(!Serial1.available());
        
        data = char(Serial1.read());
        Serial.print(String(data, HEX));
        Serial.print(" ");
        response+=data;
    }    
    Serial.println();
    
    Serial.print(" Checksum: ");
    while(!Serial1.available());
    Serial.println(Serial1.read());     // CHK
    
    Serial1.flush();
    
    delay(10);
    
    return response;
}

String Sphero::readResponse(){ return response; }
  