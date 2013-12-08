def makeCommandList(OS,SOURCE = "commands.txt",OUTPUT = None):
    fh = open("commands.txt","r")
    fh_py = open("commands.py",'w')
    if (not OUTPUT):
        if OS == "LINUX":
            fh_arduino = open("/home/carlitos/Dropbox/Programming/Arduino/RemoteChin/commands.h",'w')
        elif OS == "MAC":
            fh_arduino = open("/Users/Carlitos/Documents/Dropbox/Programming/Arduino/RemoteChin/commands.h",'w')
    else:
        fh_arduino = open(OUTPUT,'w')
        
    cmds = fh.read().replace('\n','').upper().split(',')
    fh.close()
    i = 0
    for cmd in cmds:
        if len(cmd) > 0:
            fh_py.write(cmd + " = '" + chr(i+65) + "'\n")
            fh_arduino.write("char " + cmd + " = '" + chr(i+65) + "';\n")
            i += 1
        else:
            del cmds[i]
        
    fh_py.close()
    fh_arduino.close()
    return cmds
