fh_o = open("GPS_raw.txt","a+")
for i in range(0,99):
    try:
        if i < 10:
            fh_i = open("GPSLO00"+str(i)+".TXT",'r')
        elif i < 100:
            fh_i = open("GPSLO0"+str(i)+".TXT",'r')
        else: ## i > 99
            fh_i = open("GPSLO"+str(i)+".TXT",'r')
    except:
        print "There is no file number", i
        continue
    else:
        print "Appending file number", i
        fh_o.write(fh_i.read())
        fh_i.close()
fh_o.close()
print "Appending done"

print "Cleaning file"
fh_i = open("GPS_raw.txt","r")
fh_s = open("sensors.txt","w+")
fh_o = open("GPS_output.txt","w+")
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
print "Job done."
