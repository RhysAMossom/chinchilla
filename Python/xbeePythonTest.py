import serial as s
from xbee import XBee

serial_port = s.Serial('/dev/tty.usbserial-A800enDC', 9600) 
xbee = XBee(serial_port)

# Continuously read and print packets
while True:
    try:
        response = xbee.wait_read_frame()
        print response
    except KeyboardInterrupt:
        break
        
ser.close()
