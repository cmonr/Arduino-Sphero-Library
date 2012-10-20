/************************************************
 Written by Cruz Monrreal II
 Created on 06-26-2012
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Bluetooth-Library
************************************************/

#include <stdint.h>
#include <Arduino.h>
#include <Sphero.h>

Sphero::Sphero(){
    Serial1.begin(115200);
    
    streamingParams.numOfPackets = 16;
}

Sphero::~Sphero(){}

//uint8_t Sphero::boost(uint16_t heading, uint8_t duration);
char Sphero::roll(short heading, char speed){
    return sendCommand(0x02, 0x30, 0x02, 0x05, speed, heading >> 8 , heading, 0xFF);
}
 char Sphero::setHeading(short heading){
    return sendCommand(0x02, 0x01, 0x0D, 0x03, heading >> 8, heading);
 }
char Sphero::setRGBColor(char red, char green, char blue){
    return sendCommand(0x02, 0x20, 0x01, 0x05, red, green, blue, 0xFF);
}
char Sphero::getRGBColor(){
    return sendCommand(0x02, 0x22, 0x06, 0x00);
}
char Sphero::setBackLED(char intensity){
    return sendCommand(0x02, 0x21, 0x04, 0x02, intensity);
}
//void Sphero::setRotationRate(uint8_t rate);
char Sphero::rotateHeadingBy(short heading){
    return sendCommand(0x02, 0x01, 0x03, 0x03, heading >> 8 , heading);
}
//void Sphero::setMotionTimeout();

char Sphero::setMotorPowers(signed short p1, signed short p2){
    char dir1 = 0x01,
         dir2 = 0x01,
         m1 = p1,
         m2 = p2;
    
    if (p1 < 0){
        m1 = p1 * -1;
        dir1 = 0x02;
    }
    
    if (p2 < 0){
        m1 = p2 * -1;
        dir2 = 0x02;
    }

    return sendCommand(0x02, 0x33, 0x0B, 0x05, dir1, m1, dir2, m2);
}
char Sphero::stop(char coast){
    return sendCommand(0x02, 0x33, 0x0C, 0x05, coast ? 0x03 : 0x00, 0x00, coast ? 0x03 : 0x00, 0x00);
}


char Sphero::setStabilization(char enable){
    return sendCommand(0x02, 0x33, 0x0A, 0x05, 0x04, 0x00, 0x04, 0x00)<<4 | sendCommand(0x02, 0x02, 0x09, 0x02, enable ? 0x01 : 0x00);
}
    
char Sphero::setStreamingData(short freq, short frames_per_sample, long int mask){
    streamingParams.count = 0;
    streamingParams.freq = freq;
    streamingParams.frames_per_sample = frames_per_sample;
    streamingParams.mask = mask;
    
    return sendCommand(0x02, 0x11, 0x07, 0x0A, (400/freq) >> 8, (400/freq), frames_per_sample >> 8, frames_per_sample, char(mask >> 24), char(mask >> 16), char(mask >> 8), char(mask), streamingParams.numOfPackets);
}

char Sphero::getOptionFlags(){
    return sendCommand(0x02, 0x36, 0x08, 0x01);
}

char Sphero::sendCommand(char DID, char CID, char SEQ, char DLEN, ...){
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
        
        sum += data;
    }
    va_end(args);
    
    // Write Checksum
    Serial1.write(char(~sum));
    
    delay(50);
    
    // Wait for Simple Response
    return readSimplePacket();
}

// Packet attribute functions

char Sphero::getMRSP(){
    return mrsp;
}
char Sphero::getSequenceNum(){
    return seq;
}
char Sphero::getID(){
    return seq;
}
char Sphero::getChecksum(){
    return chksum;
}
short Sphero::getDataLength(){
    return len-1;
}
unsigned char Sphero::getData(char num){
    return data[num];
}


char Sphero::readSimplePacket(){
    int i;
    
    // Wait for new data
    while(Serial1.available() < 5);
    
    Serial1.read();         // 0xFF
    Serial1.read();         // 0xFF
    mrsp = Serial1.read();  // MRSP
    seq = Serial1.read();   // SEQ
    len = Serial1.read();   // DLEN
    
    if (len > 32)   // Error
        return -1;
    
    for(i=0; i<len-1; i++){
        // Wait for new data
        while(!Serial1.available())
            delay(1);
        
        // Add data to fifo
        data[i] = char(Serial1.read());
    }
    
    // Wait for new data
    while(!Serial1.available()); 
    chksum = Serial1.read();     // CHK
    
    return mrsp;
}

void Sphero::readAsyncPacket(){
    int i;
    
    // Wait for new data
    while(Serial1.available() < 5);
    
    Serial1.read();         // 0xFF
    Serial1.read();         // 0xFE
    seq = Serial1.read();   // ID Code
    len = Serial1.read() << 8;  // DLEN-MSB
    len |= Serial1.read();      // DLEN-LSB
    
    if (len > 32)   // Error
        return;
    
    for(i=0; i<len-1; i++){
        // Wait for new data
        while(!Serial1.available())
            delay(1);
        
        // Add data to fifo
        data[i] = char(Serial1.read());
    }
    
    // Wait for new data
    while(!Serial1.available()); 
    chksum = Serial1.read();     // CHK
    
    // Auto-request more packets
    if (streamingParams.count++ == streamingParams.numOfPackets - 1){
        streamingParams.count = 0;
        
        // Get more packets
        setStreamingData(streamingParams.freq, streamingParams.frames_per_sample, streamingParams.mask);
    }
}
  