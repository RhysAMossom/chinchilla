import graphics as g
import random as r
import string as s
import time


def chooseColor(numColor):
    
    fh = open('listPythonColorsUNCLEAN.txt','r')
    rawText = fh.read()
    fh.close()
    
    index = rawText.find('AliceBlue')
    rawText = rawText[index:]
    rawText = rawText.replace('  ','*')
    rawText = rawText.replace("\\",'*')
    rawText = rawText.replace("}",'')
    for i in range(10):
        rawText= rawText.replace(' '+str(i),'*')
    for x in range(5):
        for i in range(10):
            rawText = rawText.replace('*'+str(i),'*')
    rawText = rawText.replace("*",'')
    rawText = rawText.replace("\n",'*')
    rawText = s.join(rawText,'')
    rawText = s.split(rawText,"*")
    rawText = rawText[:-1]

    if 0 <= numColor <= (len(rawText)-1):
        return rawText[numColor]
    else:
        raise ValueError

def bubbles(w,h,smallB,bigB,numB,textWin):
    
    if str(textWin)== '' or len(textWin) >20 or textWin == None:
        textWin = "Bubbles!"

    textWin = str(textWin)
    if w <100 or w >1200 or str(w)==None:
        w = 500

    if h <100 or h >900 or str(h)==None:
        h = 500

    if smallB <10 or smallB >50 or str(smallB) ==None:
        smallB=10

    if bigB <smallB or bigB > 100 or str(bigB) ==None:
        bigB = 100

    if numB < 0 or numB > 50:
        numB = 10

    
    window = g.GraphWin(textWin,w,h)
    for i in range(numB):
        color = chooseColor(r.randint(0,750))
        p = g.Point(r.randint(0,w),r.randint(0,h))
        c = g.Circle(p,r.randint(smallB,bigB))
        c.setFill(color),c.setOutline(color)
        c.draw(window)
        time.sleep(3*r.random())

    raw_input("Press ENTER to quit.\n\n")
