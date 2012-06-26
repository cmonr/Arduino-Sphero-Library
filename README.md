Arduino-Sphero-Library
======================

This is a -basic- Sphero Library for the Arduino.

Things needed:
 * Bluetooth Modem (http://www.sparkfun.com/products/9358)
 * Arduino (Only tested w/ Duemilanove)
 * Jumper Wires

Instructions: 
 1) Connect tx,rx pins on Bluetooth Module to pins 3,2 on Arduino
 2) Connect CTS and RTS to eachother
 3) Connect 5v and GND to Arduino 5V and GND
 4) Upload the AutoConfigBluetoothForSphero example, and run with the Serial Monitor
 5) Power cycle Arduino & Bluetooth Module (unplug & replug USB cable)
      NOTE: Upon power up, the Sphero should autoconnect
 6) Upload and run the SpinMeRightRound example
 
API:
 Coming soon. For now, reference Sphero.h for implemented functions (Yes, I need more comments, I know...)