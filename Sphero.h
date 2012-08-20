/************************************************
 Written by Cruz Monrreal II
 Created on 06-26-2012
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Bluetooth-Library
************************************************/

#ifndef Sphero_h
#define Sphero_h

#include <stdint.h>
//#include <SoftwareSerial.h>
#include <Arduino.h>
#include <Serial.h>

class Sphero{

public:
  // public methods
  Sphero(/* SoftwareSerial &serial */);
  ~Sphero();
  
  // Set
  //void boost(uint16_t heading, uint8_t duration);
  char roll( short heading, char speed );
  //void stop();
  char setRGBColor( char red,  char green,  char blue );
  char getRGBColor( void );
  char setBackLED( char intensity);
  //void setRotationRate(uint8_t rate);
  char rotateHeadingBy( short heading );
  char getOptionFlags( void );
  //void setMotionTimeout();
  //void setRawMotorValues(uint8_t l_mode, uint8_t r_mode, uint8_t l_pwr, uint8_t r_pwr);	// Special note. See Datasheet.
  
  // Get
  //void getHeading(uint16_t* data);
  char setStreamingData( short sample_freq_divisor, short frames_per_packet, long mask );
  char setStabilization( char enable );
  
  String readResponse( void );
  String readAsyncPacket( void );
  
  char getMRSP( void );
private:
  char sendSynchronousPacket( char DID, char CID, char SEQ, char DLEN, ... );
  char readResponsePacket( void );
  
  //Serial *bluetooth;
  String response;
  char mrsp;
};

#endif
