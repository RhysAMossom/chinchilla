import time as t
import serial as s

def connectToArduino():
    # Connect to Arduino board
    # Make a list of usb serial locations to test connection IFF it is unkown
    locations = ['/dev/arduino','/dev/tty.usbmodem411','/dev/tty.usbmodem621','/dev/ttyACM0','/dev/ttyACM1','/dev/ttyACM3','/dev/ttyUSB0','/dev/ttyUSB1','/dev/ttyUSB2','/dev/ttyUSB3',  
    '/dev/ttyS0','/dev/ttyS1','/dev/ttyS2','/dev/ttyS3']  
      
    for device in locations:  
        try:
            # Connect to board
            arduino = s.Serial(device, 9600)  
        except s.SerialException:  
            print "Failed to connect to ", device
            if device == locations[len(locations)-1]:
                print "No Arduino board detected."
                return -1
        else:
            break
            
    print "Connected to Arduino board on", device
    #wait for Arduino board to respond
    t.sleep(3);
    return arduino
