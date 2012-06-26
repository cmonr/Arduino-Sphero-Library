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
  //uint8_t boost(uint16_t heading, uint8_t duration);
  uint8_t roll( short heading, char speed );
  //uint8_t stop();
  uint8_t setRGBColor( char red,  char green,  char blue );
  uint8_t setBackLED( char intensity);
  //uint8_t setRotationRate(uint8_t rate);
  uint8_t rotateHeadingBy( short heading );
  //uint8_t setMotionTimeout();
  //uint8_t setRawMotorValues(uint8_t l_mode, uint8_t r_mode, uint8_t l_pwr, uint8_t r_pwr);	// Special note. See Datasheet.
  
  // Get
  //uint8_t getHeading(uint16_t* data);

  uint8_t readResponsePacket();
private:
  uint8_t sendSynchronousPacket(uint8_t DID, uint8_t CID, uint8_t SEQ, uint8_t DLEN, ...);
  SoftwareSerial *bluetooth;
  unsigned char response_buff[32];
};

#endif
