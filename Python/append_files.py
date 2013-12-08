fh_o = open("outputGPS.txt","a")
for i in range(63,99):
    try:
        fh_i = open("GPSLO0"+str(i)+".TXT",'r')
    except:
        print "There is no file number", i
        continue
    else:
        print "Appending file number", i
        fh_o.write(fh_i.read())
        fh_i.close()
fh_o.close()
print "work done"
        
