/************************************************
 Written by Cruz Monrreal II
 Created on 06-26-2012
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Bluetooth-Library
************************************************/

#ifndef Sphero_h
#define Sphero_h

#include <stdint.h>
#include <SoftwareSerial.h>

class Sphero{

public:
  // public methods
  Sphero( SoftwareSerial &serial );
  ~Sphero();
  
  // Set
  //void boost(uint16_t heading, uint8_t duration);
  void roll( short heading, char speed );
  //void stop();
  void setRGBColor( char red,  char green,  char blue );
  void getRGBColor( void );
  void setBackLED( char intensity);
  //void setRotationRate(uint8_t rate);
  void rotateHeadingBy( short heading );
  //void setMotionTimeout();
  //void setRawMotorValues(uint8_t l_mode, uint8_t r_mode, uint8_t l_pwr, uint8_t r_pwr);	// Special note. See Datasheet.
  
  // Get
  //void getHeading(uint16_t* data);

  
  String readRawResponse( void );
  String readResponseData( void );
private:
  void sendSynchronousPacket( char DID, char CID, char SEQ, char DLEN, ... );
  void readResponsePacket( void );
  SoftwareSerial *bluetooth;
  String response;
};

#endif
