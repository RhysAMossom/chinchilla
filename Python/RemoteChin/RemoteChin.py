import pyduino
import pygame as pg
import pygame.camera

from battery import *
from chronometer import *
from messageLog import *

from platform import system
if "linux" in system().lower().replace("-"," ").split():
    OS = "LINUX"
elif "darwin" in system().lower().split():
    OS = "MAC"

from makeCommandList import *
commandsList = makeCommandList(OS)#,"commands.txt", "/Users/Carlitos/Documents/Dropbox/Programming/Arduino/RemoteChinTest/commands.h")
import commands as cmd

def main():
    # Get global variables
    global log, arduino, arduinoDetected, temperatureK, bat, run

    run = True # Assume program will run
    
    # Log initialization
    LOG_PATH = "/Users/Carlitos/RemoteChinLog/" if(OS=="MAC") else "/home/carlitos/RemoteChinLog/"
    #LOG_PATH = "/Users/Carlitos/Dropbox/Programming/Python/RemoteChin/RemoteChinLog/" if(OS=="MAC") else "/home/carlitos/RemoteChinLog/"
    LOG_NAME = "RemoteChinLog"
    log = messageLog(LOG_PATH,LOG_NAME)

    # Chronometer initialization
    chrono = chronometer()
    lightsTimer = chronometer()
    fanTimer = chronometer()
    log.writeln("Program Started in " + OS + " operating system at "+ chrono.getDate())

    #Arduino Initialization
    arduino = pyduino.connectToArduino()
    if (arduino < 0):
        log.writeln("Cannot connect to Arduino. Creating Arduino Simulator file")
        arduino = messageLog(LOG_PATH,"ArduinoSim",False,True)
        arduinoDetected = False
    else:
        arduinoDetected = True
        log.writeln("Connected to Arduino.")

    # Pygame initialization 
    screen = pg.display.set_mode([640,480])    
    pg.init()
    log.writeln("PyGame initialized.")

    # Camera initialization
    screen = pg.display.set_mode([640,480])
    pg.camera.init()
    camera_detected = True
    for i in range(5):
        try:
            cam_address = "/dev/video"+str(i)
            cam = pygame.camera.Camera(cam_address,(640,480))
            # start the camera
            cam.start()
        except SystemError:
            if i >= 4:
                log.writeln("No camera found")
                camera_detected = False
            pass
        else:
            break
    
    log.writeln("Connected to camera on " + cam_address)
    log.writeln("Camera initialized.") 
    screen.blit(cam.get_image(),(0,0))
    pg.display.update()

    # Battery intialization
    bat = battery(OS,False)
    log.writeln("Battery Initialized.")
    log.writeln("Battery Max Level = " + str(bat.getMaxBatLevel()))
    log.writeln("Battery Current Level = " + str(bat.getCurBatLevel()))
    log.writeln("Battery Power Percentage = "+ str(bat.getBatPercentage())[0:4] + "%")
    log.writeln("Laptop Power Adapter Connected = " + str(bat.isPlugged()))

    # Main Program
    log.writeln("Program running.");
    while run:
        try:
            # Camera
            if camera_detected:
                screen.blit(cam.get_image(),(0,0))
                pg.display.update()
                t.sleep(0.05)
            
            # Keyboard
            for event in pg.event.get():
                if event.type == pg.QUIT:
                    writeCommand(cmd.GET_STATES)
                    t.sleep(2)
                    run = False
                     
                # User let up on a key
                if event.type == pg.KEYUP:
                    if event.key == pg.K_LEFT:
                        writeCommand(cmd.CAM_LEFT)
                    if event.key == pg.K_RIGHT:
                        writeCommand(cmd.CAM_RIGHT)
                    if event.key == pg.K_UP:
                        writeCommand(cmd.CAM_UP)
                    if event.key == pg.K_DOWN:
                        writeCommand(cmd.CAM_DOWN)
                    if event.key == pg.K_SPACE:
                        writeCommand(cmd.CAM_CENTER)
                    if event.key == pg.K_e:
                        writeCommand(cmd.CAM_SET_CENTER)
                    if event.key == pg.K_b:
                        log.writeln("Battery Max Level = " + str(bat.getMaxBatLevel()))
                        log.writeln("Battery Current Level = " + str(bat.getCurBatLevel()))
                        log.writeln("Battery Power Percentage = "+ str(bat.getBatPercentage())[0:4] + "%")
                        log.writeln("Laptop Power Adapter Connected = " + str(bat.isPlugged()))
                    if event.key == pg.K_ESCAPE:
                        writeCommand(cmd.RESET)
                        log.writeln("Beginning of End")
                        writeCommand(cmd.GET_STATES)
                        t.sleep(2)
                        run = False
                    if event.key == pg.K_p:
                        log.writeln("Requesting commands")
                        i = 0
                        for c in commandsList:
                            print "\t" + chr(i+65) +"  "+ c
                            i += 1
                    if event.key == pg.K_i:
                        log.writeln("Requesting instructions")
                        print "\tCamera:\t\tARROW KEYS\n\tCenter Cam:\tE\n\tSet Center:\tSPACEBAR\n\tOn:\t\tSHIFT\n\tOff:\t\tLower case"
                        print "\tLights:\t\tL\n\tFan:\t\tF\n\tCharger:\tC"
                        print "\tReset:\t\tR\n\tTemperature:\tT\n\tGet States:\tG"
                        print "\tTake Picture:\t\tD\n\tCommands:\tP\n\tInstructions:\tI"
                    if event.key == pg.K_l:
                        if(pg.key.get_pressed()[pg.K_RSHIFT] or pg.key.get_pressed()[pg.K_LSHIFT]):
                            writeCommand(cmd.LIGHTS_ON)
                        else:
                            writeCommand(cmd.LIGHTS_OFF)
                    if event.key == pg.K_f:
                        if(pg.key.get_pressed()[pg.K_RSHIFT] or pg.key.get_pressed()[pg.K_LSHIFT]):
                            writeCommand(cmd.FAN_ON)
                        else:
                            writeCommand(cmd.FAN_OFF)
                    if event.key == pg.K_c:
                        if(pg.key.get_pressed()[pg.K_RSHIFT] or pg.key.get_pressed()[pg.K_LSHIFT]):
                            writeCommand(cmd.CHARGER_ON)
                        else:
                            writeCommand(cmd.CHARGER_OFF)
                    if event.key == pg.K_t:
                        writeCommand(cmd.GET_TEMP)
                        print "Getting Temperature"
                        t.sleep(2)
                        print str(temperatureK)+" Kelvin"
                    if event.key == pg.K_g:
                        writeCommand(cmd.GET_STATES)
                    if event.key == pg.K_r:
                        writeCommand(cmd.RESET)
                    if event.key == pg.K_d:
                        if camera_detected:
                            image = cam.get_image()
                            screen.blit( image, ( 0, 0 ) )
                            pygame.display.update()
                            log.writeln("Taking a picture")
                            time_stamp = str(t.localtime(t.time()).tm_mon) +"-"+ str(t.localtime(t.time()).tm_mday) +" "+ str(t.localtime(t.time()).tm_hour) +"-"+ str(t.localtime(t.time()).tm_min)
                            pg.image.save(image,LOG_PATH+"images/img_"+time_stamp+".jpg")
                        
            # Battery
            if (chrono.getElapsedSec() >= 120.0):
                chrono.reset()
                cur_Bat = bat.getBatPercentage()
                log.writeln("Battery Power Percentage = "+ str(cur_Bat)[0:4] + "%%")
                if (bat.isPlugged()):
                    log.writeln("Charger is plugged")
                    if(cur_Bat > 95.0):
                        log.write("Asking arduino to unplug charger")
                        writeCommand(cmd.CHARGER_OFF)
                        t.sleep(10)
                        count = 0
                        while(bat.isPlugged() and count < 20):
                            writeCommand(cmd.CHARGER_OFF)
                            t.sleep(3)
                            count += 1
                        if (bat.isPlugged()):
                            log.writeln("Could not unplug charger")
                        else:
                            log.writeln("Charger unplugged")
                            log.writeln("Battery Power Percentage = "+ str(bat.getBatPercentage())[0:4] + "%%")
                else:#charger unplugged
                    log.writeln("Charger is unplugged")
                    if(cur_Bat < 10.0):
                        log.writeln("Asking Arduino to charge battery")
                        writeCommand(cmd.CHARGER_ON) #have to wait for arduino response
                        t.sleep(20)
                        count = 0
                        while(not bat.isPlugged() and count < 20):
                            writeCommand(cmd.CHARGER_ON)
                            t.sleep(3)
                            count += 1
                        if ( not bat.isPlugged()):
                            run = False
                            log.writeln("Could not plug charger")
                        else:
                            log.writeln("Charging Battery")
                            log.writeln("Battery Power Percentage = "+ str(bat.getBatPercentage())[0:4] + "%")

            # House Lights
            if (lightsTimer.getElapsedHrs() >= 1.0):
                lightsTimer.reset()
                if (21 < chrono.getHour() < 23):
                    writeCommand(cmd.LIGHTS_ON)
                else:
                    writeCommand(cmd.LIGHTS_OFF)
                
            # Temperature and Fan
            if (fanTimer.getElapsedMin() >= 10.0):
                fanTimer.reset()
                writeCommand(cmd.GET_TEMP)# get temp as number
                if temperatureK > 27+273.15: #if temperature is too hot
                    log.write("Temperature above limits at "+ str(temperatureK) + " Kelvin")
                    writeCommand(cmd.FAN_ON)
                else:
                    log.write("Temperature at "+ str(temperatureK) + " Kelvin")
                    writeCommand(cmd.FAN_OFF)

             # Movement
            try:
                if (arduinoDetected and (arduino.read(arduino.inWaiting()) == cmd.MOVEMENT_DETECTED)):
                    log.writeln("Movement Detected")
                    if camera_detected:
                        for i in range(1,2):
                            image = cam.get_image()
                            screen.blit( image, ( 0, 0 ) )
                            pygame.display.update()
                            log.writeln("Taking picture " + str(i))
                            time_stamp = str(t.localtime(t.time()).tm_mon) +"-"+ str(t.localtime(t.time()).tm_mday) +" "+ str(t.localtime(t.time()).tm_hour) +"-"+ str(t.localtime(t.time()).tm_min)
                            pg.image.save(image,LOG_PATH+"images/img_"+time_stamp+".jpg")
                            t.sleep(1)
            except IOError, OSError:
                log.writeln("Lost Arduino Connection. IOError or OSError.")
                run = False
                pass
        except KeyboardInterrupt:
            run = False 
    print "Program Terminated"
    pg.quit()
    arduino.close()
    log.close()

def writeCommand(command,VERBOSE = True):
    global arduinoDetected, arduino, log, bat, temperatureK, run# get global variables
    string = "\t" + command + " " + commandsList[ord(command)-65] # Log command
    log.writeln(string)
    if(command == cmd.GET_STATES):
        log.writeln("Battery Max Level = " + str(bat.getMaxBatLevel()))
        log.writeln("Battery Current Level = " + str(bat.getCurBatLevel()))
        log.writeln("Battery Power Percentage = "+ str(bat.getBatPercentage())[0:4] + "%")
        log.writeln("Laptop Power Adapter Connected = " + str(bat.isPlugged()))
    if (arduinoDetected):
        arduino.write(command) # send command to arduino
        t.sleep(2) # wait for arduino to respond
        try:
            msg_arduino = arduino.read(arduino.inWaiting())
        except IOError,OSError:
            log.writeln("Lost Arduino Connection. IOError.")
            run = False
            return
        if (command == cmd.GET_TEMP):
            for l in msg_arduino.split():
                try:
                    temperatureK = float(l)
                except ValueError:
                    pass
                else:
                    break
            msg = msg_arduino
        else:
            msg = "Arduino Says:\t" +  msg_arduino
        log.writeln(msg)
    else: # write to arduino simulator
        temperatureK = 350.0 # simulate hot temperature
        arduino.write(string)       

if __name__=='__main__':
    main()
