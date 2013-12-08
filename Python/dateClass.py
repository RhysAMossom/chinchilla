# -*- coding: cp1252 -*-
MONTHS = ['Enero','Febrero','Marzo','Abril',"Mayo","Junio",'Julio',"Agosto","Septiembre",'Octubre','Noviembre','Diciembre']
DAYS = ['Lunes','Martes','Miercoles','Jueves','Viernes','Sabado','Domingo']

class Date(object):

    def __init__(self, m, d, y):#this is the constructor
        if d > 31 or d < 1 or m < 1 or m > 12:
            raise ValueError

        self.month = m #these are called instance variables
        self.day = d
        self.year = y
        
    def __str__(self):
        month = MONTHS[self.month -1]
        return "%d de %s del %d." %(self.day,month,self.year)

    def leapYear(self):
        y = self.year
        if y%100 == 0 and y%400 != 0:
            return False
        elif y %4 == 0:
            return True
        else:
            return False

    def daysInMonth(self):
        if self.month in [1,3,5,7,8,10,12]:
            return 31
        elif self.month in [4,6,9,11]:
            return 30
        elif self.leapYear():
            return 29
        else:
            return 28

    def nextDay(self):
        m = self.month
        y = self.year
        d = self.day
        if d == self.daysInMonth():
            if m == 12:
                return Date(1,1,y+1)
            else:
                return Date(m+1,1,y)
        else:
            return Date(m,d+1,y)

    def goForward(self,days):
        current = self
        for d in range(days):
            current = current.nextDay()
        return current

    def prevDay(self):
        m = self.month
        y = self.year
        d = self.day
        if d == 1:
            if m == 1:
                return Date(12,31,y-1)
            else:
                newDate = Date(m-1,15,y)
                newDate.day = newDate.daysInMonth()
                return newDate
        else:
            return Date(m,d-1,y)

    def goBackward(self,days):
        current = self
        for d in range(days):
            current = current.prevDay()
        return current

    def dayOfWeek(self):
        m = 7
        d = 22
        y = 2010
        dow = DAYS[3]
    
    def __eq__(self,x):
        if self.month == x.month and self.day == x.day and self.year == x.year:
            return True
        else:
            return False

    def __sub__(self,R):
        daysBetween = 0
        x = R
        while not x == self:
            daysBetween += 1
            x = x.nextDay()
        return daysBetween
        
