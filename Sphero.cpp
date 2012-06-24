/*
SoftwareSerial.cpp (formerly NewSoftSerial.cpp) - 
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

The latest version of this library can always be found at
http://arduiniana.org.
*/

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
    
    bluetooth->begin(115200);
    bluetooth->print("$$$");
    delay(10);
    bluetooth->print("U,9600,N");
    delay(10);
    bluetooth->println('---');

    delay(1000);
    bluetooth->begin(9600);

    delay(1000);
}

//
// Destructor
//
Sphero::~Sphero()
{
  
}


//uint8_t Sphero::boost(uint16_t heading, uint8_t duration);
//uint8_t Sphero::roll(uint16_t heading, uint8_t speed);
//uint8_t Sphero::stop();
uint8_t Sphero::setRGBColor(unsigned char red, unsigned char green, unsigned char blue){
    return sendSynchronousPacket(0x02, 0x20, 0x01, 0x05, red, green, blue, 0x00);
}
//uint8_t Sphero::setBackLED(uint8_t intensity);
//uint8_t Sphero::setRotationRate(uint8_t rate);
//uint8_t Sphero::setHeading(uint16_t heading);
//uint8_t Sphero::setMotionTimeout();
//uint8_t Sphero::setRawMotorValues(uint8_t l_mode, uint8_t r_mode, uint8_t l_pwr, uint8_t r_pwr);

uint8_t Sphero::sendSynchronousPacket(uint8_t DID, uint8_t CID, uint8_t SEQ, uint8_t DLEN, ...){
    uint16_t i=0;
    uint8_t sum=0, tmp;
    va_list args;
    
    bluetooth->write(0xFF);
    bluetooth->write(0xFE);
    bluetooth->write(uint8_t(DID));
    bluetooth->write(uint8_t(CID));
    bluetooth->write(uint8_t(SEQ));
    bluetooth->write(uint8_t(DLEN));
    
    va_start(args, DLEN);
    for(; i<DLEN-1; i++){
        tmp = va_arg(args, int);
        bluetooth->write(tmp);
        sum += uint8_t(tmp);
    }
    va_end(args);
    
    bluetooth->write(~sum);
    
    return readResponsePacket();
}

uint8_t Sphero::readResponsePacket(){
    while(bluetooth->available())
}
