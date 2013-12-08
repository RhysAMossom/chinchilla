'''
Created on May 20, 2011
@author: Carlos Chinchilla

This program will communicate with an Arduino UNO board through serial connection.
It will send a signal that will toggle the light mode of the CATA Safety light.

message type:
board name: "arduino"

Autonomous send:
Radio-Controlled send:
Off-Mode send:

'''

import serial


arduino = serial.Serial('/dev/ttyUSB0', 9600)
arduino.write('5')
