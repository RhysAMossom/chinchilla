fh_i = open("inputGPS.txt","r")
fh_s = open("sensors.txt","w")
fh_o = open("outputGPS.txt","w")
line = fh_i.readline()
while (line):
    print line
    if (",sensors" in line):
        fh_s.write(line)
    elif not("$GPGSA,A,1,,,,,,,,,,,,,,,*1E" in line):
        fh_o.write(line)
        
    line = fh_i.readline()
fh_i.close()
fh_o.close()
fh_s.close()
print "job done"
