Arduino-Sphero-Library
======================

This is a -basic- Sphero Library for the Arduino.

Things needed:
* Bluetooth Modem (http://www.sparkfun.com/products/9358)
* Arduino Mega 2560
* Jumper Wires

Instructions: 
# Connect tx,rx pins on Bluetooth Module to TX1, RX1 on Arduino Mega
# Connect CTS and RTS to eachother
# Connect 5v and GND to Arduino 5V and GND
# Shake on Sphero
# Upload the AutoConfigBluetoothForSphero example, and run with the Serial Monitor
# Power cycle Arduino & Bluetooth Module (unplug & replug USB cable)
: NOTE: Upon power up, the Sphero should autoconnect
# Upload and run any of the examples
 
API:
: Coming soon. For now, reference Sphero.h for implemented functions and examples (Yes, I need more comments, I know...)