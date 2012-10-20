Arduino-Sphero-Library
======================

This is a -basic- Sphero Library for the Arduino.

Things needed:
* Bluetooth Modem (http://www.sparkfun.com/products/9358)
* Arduino Mega 2560
* Jumper Wires

Instructions: 
1. Connect tx,rx pins on Bluetooth Module to TX1, RX1 on Arduino Mega
2. Connect CTS and RTS to eachother
3. Connect 5v and GND to Arduino 5V and GND
4. Shake on Sphero
5. Upload the AutoConfigBluetoothForSphero example, and run with the Serial Monitor
6. Power cycle Arduino & Bluetooth Module (unplug & replug USB cable)
: NOTE: Upon power up, the Sphero should autoconnect
7. Upload and run any of the examples
 
API:
: Coming soon. For now, reference Sphero.h for implemented functions and examples (Yes, I need more comments, I know...)