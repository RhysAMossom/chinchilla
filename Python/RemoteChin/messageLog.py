import time as t

class messageLog(object):
    def __init__(self, LOG_PATH, LOG_NAME, VERBOSE=True,SIM=False):
        self.path = LOG_PATH
        time_stamp = " " + str(t.localtime(t.time()).tm_mon) +"-"+ str(t.localtime(t.time()).tm_mday) +" "+ str(t.localtime(t.time()).tm_hour) +"-"+ str(t.localtime(t.time()).tm_min) +".txt"
        self.name = LOG_NAME + time_stamp
        self.verbose = VERBOSE
        self.sim = SIM
        try:
            self.fh = open(self.path + self.name ,"w")
        except IOError:
            if(self.verbose):
                print "Could not open file " + self.path + self.name
            self.fh = open(self.name,"w")
            self.path = ""

    def write(self, string, TIMESTAMP = True):
        if(self.verbose):
            print string
        if(TIMESTAMP):
            string = t.asctime(t.localtime(t.time())) + "\t" + str(string)
        if self.sim:
            string = string + "\n"
        self.fh.write(string)

    def writeln(self, string, TIMESTAMP = True):
        if(self.verbose):
            print string
        if(TIMESTAMP):
            string = t.asctime(t.localtime(t.time())) + "\t" + str(string)
        self.fh.write(string)
        self.fh.write("\n")
    
    def getFileLocation(self):
        return self.path

    def close(self):
        if(self.verbose):
            print "\n\n%s log closed" %self.name
        self.fh.write("\n" + t.asctime(t.localtime(t.time())) + "\t" + "end of log.")
        self.fh.close()

        
