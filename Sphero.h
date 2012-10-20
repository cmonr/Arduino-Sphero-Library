/************************************************
 Written by Cruz Monrreal II
 Created on 06-26-2012
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Bluetooth-Library
************************************************/

#ifndef Sphero_h
#define Sphero_h

#include <stdint.h>
#include <Arduino.h>
#include <Serial.h>

#define SPHERO_IMU_YAW      0x00010000
#define SPHERO_IMU_ROLL     0x00020000
#define SPHERO_IMU_PITCH    0x00040000

class Sphero{

public:
  // public methods
  Sphero();
  ~Sphero();
  
  // Set
  //void boost(uint16_t heading, uint8_t duration);
  char roll( short heading, char speed );
  //void stop();
  char setHeading( short heading );
  char setRGBColor( char red,  char green,  char blue );
  char getRGBColor( void );
  char setBackLED( char intensity );
  //void setRotationRate(uint8_t rate);
  char rotateHeadingBy( short heading );
  char getOptionFlags( void );
  //void setMotionTimeout();
  
  
  // setRawMotorValues
  //  *** Disables Stabilization
  //  *** Will need to be reenabled
  char setMotorPowers( signed short m1, signed short m2 );
  char stop( char coast );
  
  
  // Get
  char setStreamingData( short sample_freq_divisor, short frames_per_packet, long int mask );
  char setStabilization( char enable );
  
  // Packet attributes
  char getMRSP( void );
  char getSequenceNum( void );
  char getID( void );
  char getChecksum( void );
  short getDataLength( void );
  unsigned char getData( char num );
  
  void readAsyncPacket( void );
  
private:
  char sendCommand( char DID, char CID, char SEQ, char DLEN, ... );
  char readSimplePacket( void );
  
  char mrsp;
  char seq;
  short len;
  unsigned char data[32];
  char chksum;
  
  typedef struct {
    char count;
    char numOfPackets;
    
    short freq;
    short frames_per_sample;
    long mask;
  } StreamingParams;
  StreamingParams streamingParams;
};

#endif
