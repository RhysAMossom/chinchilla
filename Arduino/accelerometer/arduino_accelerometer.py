#! /usr/bin/env python
"""
Arduino Accelerometer code, using a MMA8452

Written by Carlos Chinchilla
"""

import serial
import time
from arduino_framework import *
import curses
import optparse

def main(screen, options):
    arduino = Arduino(port=options.port)
    curses.curs_set(0)
    screen.clear()
    
    count = 1
    tic = time.time()
    # reset minimums and maximums
    accelerations = arduino.get_readings()
    gx = gx_max = gx_min = accelerations[0]
    gy = gy_max = gy_min = accelerations[1]
    gz = gz_max = gz_min = accelerations[2]
    offset = (curses.LINES - 5) / 2
    while True:
        count += 1
        accelerations = arduino.get_readings()
        gx = accelerations[0]
        gy = accelerations[1]
        gz = accelerations[2]
        if gx > gx_max: gx_max = gx
        if gy > gy_max: gy_max = gy
        if gz > gz_max: gz_max = gz
        if gx < gx_min: gx_min = gx
        if gy < gy_min: gy_min = gy
        if gz < gz_min: gz_min = gz
        screen.clear()
        screen.addstr(0,0,"%d\t\t%fs" %(count, time.time()-tic))
        screen.addstr(1,0,"g\tcurrent\tmax\tmin")
        screen.addstr(2,0,"x:\t%.4f\t%.4f\t%.4f\n" % (gx,gx_max,gx_min))
        screen.addstr(3,0,"y:\t%.4f\t%.4f\t%.4f\n" % (gy,gy_max,gy_min))
        screen.addstr(4,0,"z:\t%.4f\t%.4f\t%.4f\n" % (gz,gz_max,gz_min))
        
        screen.addstr(offset,0,curses.COLS*".")
        screen.addstr(offset+int(round(gx*10)),20,5*"X")
        screen.addstr(offset+int(round(gy*10)),40,5*"Y")
        screen.addstr(offset+int(round(gz*10)),60,5*"Z")
        screen.refresh()
        
if __name__ == '__main__':
    parser = optparse.OptionParser()
    parser.add_option("-p", "--port ", dest="port", default='/dev/arduino0', help="arduino port or path address, default '/dev/arduino0'")
    options,args = parser.parse_args()
    curses.wrapper(main, options)
