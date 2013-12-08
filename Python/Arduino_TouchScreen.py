import graphics as g
import time as t
import serial as s        


width = 900
height = 900
spacer = 10

def connectToArduino():

    # Connect to Arduino board
    i = 0
    # Make a list of usb serial locations to test connection IFF it is unkown
    locations = ['/dev/arduino','/dev/tty.usbmodem411','/dev/ttyACM0','/dev/ttyACM1','/dev/ttyACM3','/dev/ttyUSB0','/dev/ttyUSB1','/dev/ttyUSB2','/dev/ttyUSB3',  
    '/dev/ttyS0','/dev/ttyS1','/dev/ttyS2','/dev/ttyS3']  
      
    for device in locations:  
        try:
            # Connect to board
            a = s.Serial(device, 9600)  
        except:  
            print "Failed to connect to",device
            if i == len(locations):
                print "No Arduino board detected."
            i+= 1
            
    print "Connected to Arduino board on", device
    #wait for Arduino board to respond
    t.sleep(3);
    return a

def main():
    arduino = connectToArduino();
    w = g.GraphWin("Touch Screen",width,height)  


    box = g.Rectangle(g.Point(spacer, spacer),g.Point(width-spacer, height-spacer))
    box.draw(w)

    pointer = g.Circle(g.Point(width/2, height/2), 20)
    pointer.setFill('blue')
    pointer.draw(w)

    while True:
        msg = arduino.read()
        if len(msg) > 0:
            while msg[len(msg)-1] != 'e' :
                msg += arduino.read()
            arduino.flush();
            print msg
            coordinates = msg[msg.find('s')+1:len(msg)-1].split('.')
            print coordinates
            x = int(coordinates[0])
            y = int(coordinates[1])
            #p = int(coordinates[2])
            pointer.move(x-pointer.getCenter().getX(),y-pointer.getCenter().getY())
            #pointer.fill(p)

            w.update()
    raw_input("<ENT> to quit.")

if __name__=='__main__':
    main()
