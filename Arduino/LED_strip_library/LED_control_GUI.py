#! /usr/bin/env python
"""
Author: Carlos Chinchilla
2013-2014

CIDERWARE LICENSE - TG version
The code is free to use and modify by the Thunder Gumbo community and
no one else. If you find the code useful and see the author
chinchillin' at a bar you may thank him with a cold apple cider.
"""

import sys
import time

try:
    import serial
except ImportError:
    print("install PySerial http://pyserial.sourceforge.net/")

from Tkinter import *
import ttk
import tkColorChooser

import protocol as p
if not p.passed:
    print("malformed protocol file, quitting.")
    quit()

class ArduinoError(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

class Arduino(serial.Serial):
    def __init__(self, port=None, baudrate=9600):
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
                # If we reach the end of the array, no device has been found
                if p == ports[len(ports)-1]:
                    raise ArduinoError("No Arduino board detected. Did you try installing the udev rule?")
            else:
                self = open_connection
                time.sleep(3) # wait for arduino to finish resetting after connection
                break

# Event handlers

def choose_color(initialcolor,*args):
    xRGB = initialcolor
    RGB, hexRGB = tkColorChooser.askcolor(parent=mainframe,initialcolor=xRGB.get())
    if RGB is not None:
        R.set(RGB[0])
        G.set(RGB[1])
        B.set(RGB[2])
        xRGB.set(hexRGB)
        sRGB.set("RGB = %d,%d,%d - %s" % (R.get(),G.get(),B.get(),xRGB.get()))
        canvas.itemconfig(color_box,fill=xRGB.get())
        print("Color Selected: R + G + B-xRGB")
        hexRGB = xRGB.get().replace('#','').strip()
        msg = "%s%s%s-%s\n" % (chr(R.get()),chr(G.get()),chr(B.get()),hexRGB)
        print(msg)

def set_color(*args):
    print("UID + COLOR + R + G + B-xRGB")
    msg = "%s%s%s%s%s-%s\n" % (UID.get(),p.COLOR,chr(R.get()),chr(G.get()),chr(B.get()),xRGB.get())
    print(msg)        

def check_box_change(com,*args):
    if com == p.TOGGLE:
        value = effect_continuity.get()
    elif com == p.THEME_TOGGLE:
        value = theme_continuity.get()
    else:
        print("unhandled check box with command %s" % str(com))
    print("UID + TOGGLE + TOGGLE_VALUE")
    msg = "%s%s%s\n" % (UID.get(),com,value)
    print(msg)

def button_down(com,code,*args):
    print("UID + COMMAND + EFFECT_CODE")
    # first check if we are using a 1-byte packet
    if code in [p.RANDOM_COLOR, p.RANDOM_THEME, p.RANDOM_EFFECT, p.RAINBOW_EFFECT]:
        com =   ''
    elif code in [p.FLASH_EFFECT, p.WIPE_EFFECT]:
        com = code
        code = "%s%s%s-%s" % (chr(R.get()),chr(G.get()),chr(B.get()),xRGB.get())
    msg = "%s%s%s\n" % (UID.get(),com,code)
    print(msg)

def effect_down(*args):
    try:
        e = int(effect.get())
    except ValueError:
        print("could not convert %s to integer" % str(effect.get()))
        return
    print("UID + EFFECT + EFFECT_NUMBER")
    msg = "%s%s%s\n" % (UID.get(),p.EFFECT,chr(e))
    print(msg)

# Main program

if __name__ == '__main__':
    #if sys.argv[1] != '':
    #    port = sys.argv[1]
    #else:
    #    port = '/dev/arduino0'
    #print("using port %s" % port)
    try:
        #arduino = Arduino(port=port)
        #arduino.write(chr(0)+chr(0)+chr(0)+'\n')
        #import array
        #array.array('B', [0xc0, 0x04, 0x00]).tostring()
        

        
        root = Tk()
        root.title("LED Strip Controller by Chinchillashark")
        mainframe = ttk.Frame(root, padding="3 3 12 12",cursor='gumby')
        mainframe.grid(column=0,row=0,sticky=(N, W, E, S))
        mainframe.columnconfigure(0,weight=1)
        mainframe.rowconfigure(0, weight=1)
        
        # Controls
        # UIDs
        UID =  StringVar()
        uids = ('','0','1','2','3','4','5','6','7','8','9')
        ttk.Label(mainframe, text='Strip #').grid(column=1, row=1, sticky=(W,E))
        ttk.OptionMenu(mainframe, UID, *uids).grid(column=2,row=1, sticky=(W,E))
        UID.set('1')

        # Effects
        effects_frame = ttk.Labelframe(mainframe,text='Effects',padding="3 3 12 12",)
        effects_frame.grid(column=1,row=2,columnspan=2,sticky=(N, W, E, S))

        # Effect number box
        effect = StringVar()
        effect_entry = ttk.Entry(effects_frame,width=8, textvariable=effect)
        effect_entry.grid(column=2,row=1, sticky=(W,E))
        ttk.Label(effects_frame, text='Effect #').grid(column=1, row=1, sticky=(W,E))
        ttk.Button(effects_frame, text="Set Effect", command=effect_down).grid(column=1,row=2,columnspan=2,sticky=(W,E))
        effect.set('1')
        # Effects buttons
        c = 1
        r = 4
        for effect_name, effect_code in p.effects_list.iteritems():
            b = ttk.Button(effects_frame, text=effect_name, command=lambda code=effect_code,com=p.EFFECT:button_down(com,code)).grid(column=c,row=r,sticky=W)
            c += 1
            if c == 3:
                r += 1
                c = 1
        # Effect toggle
        effect_continuity = StringVar()
        ttk.Checkbutton(effects_frame, variable=effect_continuity, 
                text='Effects continuity',onvalue=p.ON, offvalue=p.OFF,
                command=lambda com=p.TOGGLE:check_box_change(com)).grid(column=1,row=3,sticky=(W))
        
        # Themes
        themes_frame = ttk.Labelframe(mainframe,text='Themes',padding="3 3 12 12",)
        themes_frame.grid(column=3,row=2,columnspan=2, sticky=(N, W, E, S))

        # Theme buttons
        c = 1
        r = 2
        for theme_name, theme_code in p.themes_list.iteritems():
            b = ttk.Button(themes_frame, text=theme_name, command=lambda code=theme_code,com=p.THEME_SELECT:button_down(com,code)).grid(column=c,row=r,sticky=W)
            c += 1
            if c == 3:
                r += 1
                c = 1
        
        # Theme toggle
        theme_continuity = StringVar()
        ttk.Checkbutton(themes_frame, variable=theme_continuity, 
                text='Themes continuity',onvalue=p.ON, offvalue=p.OFF,
                command=lambda com=p.THEME_TOGGLE:check_box_change(com)).grid(column=1,row=1,sticky=(W))
        
        # Colors        
        colors_frame = ttk.Labelframe(mainframe,text='Colors',padding="3 3 12 12",)
        colors_frame.grid(column=5,row=2,columnspan=2,sticky=(N, W, E, S))
        # RGB colors
        R = IntVar()
        R.set(0)
        G = IntVar()
        G.set(99)
        B = IntVar()
        B.set(255)
        xRGB = StringVar()
        xRGB.set('#0063ff')
        sRGB = StringVar()
        ttk.Label(colors_frame, textvariable=sRGB).grid(column=1, row=1, sticky=(W,E))
        sRGB.set("RGB = %d,%d,%d - %s" % (R.get(),G.get(),B.get(),xRGB.get()))

        # Choose Color button
        ttk.Button(colors_frame, text="Select Color", command=lambda initialcolor=xRGB:choose_color(initialcolor)).grid(column=1,row=3,columnspan=2, sticky=(W,E))
        ttk.Button(colors_frame, text="Set Color", command=set_color).grid(column=1,row=4,columnspan=2, sticky=(W,E))
        ttk.Button(colors_frame, text="RANDOM COLOR", command=lambda code=p.RANDOM_COLOR,com=p.RANDOM_COLOR:button_down(com,code)).grid(column=1,row=5,columnspan=2,sticky=(W,E))
        # Chosen color box
        canvas = Canvas(colors_frame, bg='white', width = 100, height=30)
        canvas.grid(column=1,row=2,columnspan=2,sticky=(W))
        color_box = canvas.create_rectangle(0, 0, 101, 31, fill=xRGB.get())
        
        for child in effects_frame.winfo_children():
            child.grid_configure(padx=5,pady=5)
            
        for child in themes_frame.winfo_children():
            child.grid_configure(padx=5,pady=5)
            
        for child in colors_frame.winfo_children():
            child.grid_configure(padx=5,pady=5)
        
        for child in mainframe.winfo_children():
            child.grid_configure(padx=5,pady=5)
        
        effect_entry.focus()
        root.bind("<Escape>", lambda e: e.widget.quit())
        root.bind('<Return>', effect_down)
        root.mainloop()

    except KeyboardInterrupt:
        #arduino.close()
        print("cancelled by user")
    finally:
        print("done")

# TO DO:
# * test messages with arduino
# * sending full packet instead of only effect number
# *
# *
