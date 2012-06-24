/*
SoftwareSerial.h (formerly NewSoftSerial.h) - 
Multi-instance software serial library for Arduino/Wiring
-- Interrupt-driven receive and other improvements by ladyada
   (http://ladyada.net)
-- Tuning, circular buffer, derivation from class Print/Stream,
   multi-instance support, porting to 8MHz processors,
   various optimizations, PROGMEM delay tables, inverse logic and 
   direct port writing by Mikal Hart (http://www.arduiniana.org)
-- Pin change interrupt macros by Paul Stoffregen (http://www.pjrc.com)
-- 20MHz processor support by Garrett Mace (http://www.macetech.com)
-- ATmega1280/2560 support by Brett Hagman (http://www.roguerobotics.com/)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

Datasheet: https://s3.amazonaws.com/docs.gosphero.com/api/Sphero_API_1.20.pdf


The latest version of this library can always be found at
http://arduiniana.org.
*/

#ifndef Sphero_h
#define Sphero_h

#include <stdint.h>
#include <SoftwareSerial.h>

/******************************************************************************
* Definitions
******************************************************************************/

class Sphero{

public:
  // public methods
  Sphero( SoftwareSerial &serial );
  ~Sphero();
  
  // Set
  //uint8_t boost(uint16_t heading, uint8_t duration);
  //uint8_t roll(uint16_t heading, uint8_t speed);
  //uint8_t stop();
  uint8_t setRGBColor(unsigned char red, unsigned char green, unsigned char blue);
  //uint8_t setBackLED(uint8_t intensity);
  //uint8_t setRotationRate(uint8_t rate);
  //uint8_t setHeading(uint16_t heading);
  //uint8_t setMotionTimeout();
  //uint8_t setRawMotorValues(uint8_t l_mode, uint8_t r_mode, uint8_t l_pwr, uint8_t r_pwr);	// Special note. See Datasheet.
  
  // Get
  //uint8_t getHeading(uint16_t* data);

private:
  uint8_t sendSynchronousPacket(uint8_t DID, uint8_t CID, uint8_t SEQ, uint8_t DLEN, ...);
  SoftwareSerial *bluetooth;
  unsigned char response_buff[32];
};



#endif
