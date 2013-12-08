import time as t

class chronometer():
    def __init__(self):
        self.startTime = t.time()

    def reset(self):
        self.startTime = t.time()

    def getDate(self):
        return t.asctime(t.localtime(t.time()))

    def getElapsedSec(self):
        return t.time() - self.startTime

    def getElapsedMin(self):
        return self.getElapsedSec()/60.0

    def getElapsedHrs(self):
        return self.getElapsedMin()/60.0
    
    def getElapsedDays(self):
        return self.getElapsedMin()/24.0

    def getMin(self):
        return t.localtime(t.time())[4]

    def getHour(self):
        return t.localtime(t.time())[3]
