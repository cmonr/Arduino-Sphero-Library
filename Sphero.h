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
  char setRGBColor( char red,  char green,  char blue );
  char getRGBColor( void );
  char setBackLED( char intensity );
  //void setRotationRate(uint8_t rate);
  char rotateHeadingBy( short heading );
  char getOptionFlags( void );
  //void setMotionTimeout();
  //void setRawMotorValues(uint8_t l_mode, uint8_t r_mode, uint8_t l_pwr, uint8_t r_pwr);	// Special note. See Datasheet.
  
  // Get
  //void getHeading(uint16_t* data);
  char setStreamingData( short sample_freq_divisor, short frames_per_packet, long int mask );
  char setStabilization( char enable );
  
  // Packet attributes
  char getMRSP( void );
  char getSequenceNum( void );
  char getID( void );
  char getChecksum( void );
  short getDataLength( void );
  //char[] getDataPointer( void );
  char getData( char num );
  
  void readAsyncPacket( void );
  
private:
  char sendCommand( char DID, char CID, char SEQ, char DLEN, ... );
  char readSimplePacket( void );
  
  //Serial *bluetooth;
  char mrsp;
  char seq;
  short len;
  char data[32];
  char chksum;
};

#endif
