#! /usr/bin/env python
"""
Arduino board framework.

Written by Carlos Chinchilla
"""

import sys
import serial
import time

class ArduinoError(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

class Arduino(serial.Serial):
    def __init__(self, port=None, baudrate=9600):
        self.error_count = 0
        self.max_errors = 10
        self.unlimited_errors = False
        
        # connect to arduino
        if port is not None:
            ports = [port]
        else:
            # create a list of possible arduino port names
            ports = ['/dev/arduino'] 
            for i in range(100):
                ports.append('/dev/arduino%d'%i) # using udev rules
                #ports.append('/dev/ttyACM%d'%i)
                #ports.append('/dev/ttyUSB%d'%i)
                #ports.append('/dev/ttyS%d'%i)
                #ports.append('COM%d'%i)
        for p in ports:
            try:
                # Connect to board
                open_connection = serial.Serial.__init__(self,
                    port=port,
                    baudrate=baudrate
                    ) 
            except serial.SerialException:  
                # print "Failed to connect to ", device
                # If we reach the end of the array, no device has been found
                if p == ports[len(ports)-1]:
                    raise ArduinoError("No Arduino board detected. Did you try installing the udev rule?")
            else:
                self = open_connection
                time.sleep(2)
                break
        time.sleep(1) # wait for arduino to finish resetting after connection

    def get_readings(self):
        """
        To be used with /bot-technician-tests/automated_tests/sensors/Humidity_Temperature
        or /bot-technician-tests/Test_Fixtures/Arduino_Accelerometer/Basic_Sketch
        """
        self.error_count = 0
        
        while self.error_count < self.max_errors:
            reading_raw = self.readline().strip()
            
            if reading_raw.strip() != '' and len(reading_raw.strip().split(';')) >= 3:
                readings = reading_raw.strip().split(';')

                # convert to float
                try:
                    for i in range(len(readings)):
                        readings[i] = float(readings[i])
                    return readings
                except:
                    self.error_count += 1
                    pass
            else:
                self.error_count += 1
            if self.error_count >= self.max_errors and not self.unlimited_errors:
                raise ArduinoError("%d consecutive failed attemps to read data. Last data received: '%s'" % (self.max_errors,reading_raw))

    def get_humidity(self):
        return self.get_readings()[0]

    def get_temperature_C(self):
        return self.get_readings()[1]

    def get_temperature_F(self):
        return self.get_readings()[2]

    def get_accelerations(self):
        accelerations = self.get_readings()
        g = 9.80665 #m/s^2
        for a in accelerations:
            try:
                a *= g
            except:
                pass
        return accelerations

    def get_g_s(self):
        return self.get_readings()

if __name__ == '__main__':
    try:
        arduino = Arduino(port='/dev/arduino0')
        while True:
            readings = arduino.get_readings()
            r1 = readings[0]
            r2 = readings[1]
            r3 = readings[2]
            sys.stdout.write("\t%.4f\t%.4f\t%.4f" % (r1,r2,r3))
            sys.stdout.flush()
            sys.stdout.write('\r')
            sys.stdout.flush()
    except KeyboardInterrupt:
        arduino.close()
        
# TO DO: implement enter and exit functions for arduino object
# def __enter__(self)
# def __exit__(self, type, value, traceback)
