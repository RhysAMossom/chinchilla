import graphics as g
from inButton import *
from cleanTextFile import *
import random as r
import time as t

def chooseColor():
    colorList = cleanTextFile()

    width = 1020
    height = 410
    sqrBox = 20
    xF1 = 10
    xF2 = width - xF1
    yF1 = height - 10
    yF2 = 100

    win = g.GraphWin("Python Color Palette Retriever",width,height)
    frame = g.Rectangle(g.Point(xF1,yF1),g.Point(xF2,yF2))
    frame.draw(win)

    x1 = xF1
    y1 = yF2 + sqrBox
    x2 = xF1 + sqrBox
    y2 = yF2

    for i in range(len(colorList)-1):
 
        pixel = g.Rectangle(g.Point(x1,y1),g.Point(x2,y2))
        pixel.setFill(colorList[i]); pixel.setOutline(colorList[i])
        pixel.draw(win)

        if x2 == xF2:
            x1 = xF1
            y1 += sqrBox
            x2 = xF1 + sqrBox
            y2 += sqrBox
            continue
        
        x1 += sqrBox
        x2 += sqrBox

    lastBox = g.Rectangle(g.Point(xF1,10),g.Point(xF1+(2*sqrBox),10+(2*sqrBox)))
    lastBox.setFill(colorList[-1]); lastBox.setOutline(colorList[-1])
    lastBox.draw(win)

    msg = 'Click on a box to get its color name.'
    label = g.Text(g.Point(frame.getCenter().getX(),50),msg)
    label.setSize(26)
    label.draw(win)

    randButt = g.Rectangle(g.Point(xF2-120,50),g.Point(xF2,10))
    randButt.setFill('pink');randButt.setOutline('red')
    randButt.draw(win)

    randText = g.Text(randButt.getCenter(),"Random")
    randText.setSize(26); randText.setFace('helvetica');randText.setStyle('bold')
    randText.draw(win)

    while True:
        click = win.getMouse()
        
        if inButton(click,randButt):
            chosenColor = r.choice(colorList)
            break
        elif not inButton(click,frame) and not inButton(click,lastBox):
            continue
        else:
            if inButton(click,lastBox):
                chosenColor = colorList[-1]
                break
            else:
                xClick = click.getX()
                yClick = click.getY()
            
                if xF1 <= xClick < xF1+sqrBox:
                    xNum = 0
                elif xF1+sqrBox <= xClick < xF1+2*sqrBox:
                    xNum = 1
                elif xF1+2*sqrBox <= xClick < xF1+3*sqrBox:
                    xNum = 2
                elif xF1+3*sqrBox <= xClick < xF1+4*sqrBox:
                    xNum = 3
                elif xF1+4*sqrBox <= xClick < xF1+5*sqrBox:
                    xNum = 4
                elif xF1+5*sqrBox <= xClick < xF1+6*sqrBox:
                    xNum = 5
                elif xF1+6*sqrBox <= xClick < xF1+7*sqrBox:
                    xNum = 6
                elif xF1+7*sqrBox <= xClick < xF1+8*sqrBox:
                    xNum = 7
                elif xF1+8*sqrBox <= xClick < xF1+9*sqrBox:
                    xNum = 8
                elif xF1+9*sqrBox <= xClick < xF1+10*sqrBox:
                    xNum = 9
                elif xF1+10*sqrBox <= xClick < xF1+11*sqrBox:
                    xNum = 10
                elif xF1+11*sqrBox <= xClick < xF1+12*sqrBox:
                    xNum = 11
                elif xF1+12*sqrBox <= xClick < xF1+13*sqrBox:
                    xNum = 12
                elif xF1+13*sqrBox <= xClick < xF1+14*sqrBox:
                    xNum = 13
                elif xF1+14*sqrBox <= xClick < xF1+15*sqrBox:
                    xNum = 14
                elif xF1+15*sqrBox <= xClick < xF1+16*sqrBox:
                    xNum = 15
                elif xF1+16*sqrBox <= xClick < xF1+17*sqrBox:
                    xNum = 16
                elif xF1+17*sqrBox <= xClick < xF1+18*sqrBox:
                    xNum = 17
                elif xF1+18*sqrBox <= xClick < xF1+19*sqrBox:
                    xNum = 18
                elif xF1+19*sqrBox <= xClick < xF1+20*sqrBox:
                    xNum = 19
                elif xF1+20*sqrBox <= xClick < xF1+21*sqrBox:
                    xNum = 20
                elif xF1+21*sqrBox <= xClick < xF1+22*sqrBox:
                    xNum = 21
                elif xF1+22*sqrBox <= xClick < xF1+23*sqrBox:
                    xNum = 22
                elif xF1+23*sqrBox <= xClick < xF1+24*sqrBox:
                    xNum = 23
                elif xF1+24*sqrBox <= xClick < xF1+25*sqrBox:
                    xNum = 24
                elif xF1+25*sqrBox <= xClick < xF1+26*sqrBox:
                    xNum = 25
                elif xF1+26*sqrBox <= xClick < xF1+27*sqrBox:
                    xNum = 26
                elif xF1+27*sqrBox <= xClick < xF1+28*sqrBox:
                    xNum = 27
                elif xF1+28*sqrBox <= xClick < xF1+29*sqrBox:
                    xNum = 28
                elif xF1+29*sqrBox <= xClick < xF1+30*sqrBox:
                    xNum = 29
                elif xF1+30*sqrBox <= xClick < xF1+31*sqrBox:
                    xNum = 30
                elif xF1+31*sqrBox <= xClick < xF1+32*sqrBox:
                    xNum = 31
                elif xF1+32*sqrBox <= xClick < xF1+33*sqrBox:
                    xNum = 32
                elif xF1+33*sqrBox <= xClick < xF1+34*sqrBox:
                    xNum = 33
                elif xF1+34*sqrBox <= xClick < xF1+35*sqrBox:
                    xNum = 34
                elif xF1+35*sqrBox <= xClick < xF1+36*sqrBox:
                    xNum = 35
                elif xF1+36*sqrBox <= xClick < xF1+37*sqrBox:
                    xNum = 36
                elif xF1+37*sqrBox <= xClick < xF1+38*sqrBox:
                    xNum = 37
                elif xF1+38*sqrBox <= xClick < xF1+39*sqrBox:
                    xNum = 38
                elif xF1+39*sqrBox <= xClick < xF1+40*sqrBox:
                    xNum = 39
                elif xF1+40*sqrBox <= xClick < xF1+41*sqrBox:
                    xNum = 40
                elif xF1+41*sqrBox <= xClick < xF1+42*sqrBox:
                    xNum = 41
                elif xF1+42*sqrBox <= xClick < xF1+43*sqrBox:
                    xNum = 42
                elif xF1+43*sqrBox <= xClick < xF1+44*sqrBox:
                    xNum = 43
                elif xF1+44*sqrBox <= xClick < xF1+45*sqrBox:
                    xNum = 44
                elif xF1+45*sqrBox <= xClick < xF1+46*sqrBox:
                    xNum = 45
                elif xF1+46*sqrBox <= xClick < xF1+47*sqrBox:
                    xNum = 46
                elif xF1+47*sqrBox <= xClick < xF1+48*sqrBox:
                    xNum = 47
                elif xF1+48*sqrBox <= xClick < xF1+49*sqrBox:
                    xNum = 48
                else:
                    xNum = 49

                if yF1 >= yClick > yF1-sqrBox:
                    yNum = 700
                elif yF1-sqrBox >= yClick > yF1 -2*sqrBox:
                    yNum = 650
                elif yF1-2*sqrBox >= yClick > yF1 -3*sqrBox:
                    yNum = 600
                elif yF1-3*sqrBox >= yClick > yF1 -4*sqrBox:
                    yNum = 550
                elif yF1-4*sqrBox >= yClick > yF1 -5*sqrBox:
                    yNum = 500
                elif yF1-5*sqrBox >= yClick > yF1 -6*sqrBox:
                    yNum = 450
                elif yF1-6*sqrBox >= yClick > yF1 -7*sqrBox:
                    yNum = 400
                elif yF1-7*sqrBox >= yClick > yF1 -8*sqrBox:
                    yNum = 350
                elif yF1-8*sqrBox >= yClick > yF1 -9*sqrBox:
                    yNum = 300
                elif yF1-9*sqrBox >= yClick > yF1 -10*sqrBox:
                    yNum = 250
                elif yF1-10*sqrBox >= yClick > yF1 -11*sqrBox:
                    yNum = 200
                elif yF1-11*sqrBox >= yClick > yF1 -12*sqrBox:
                    yNum = 150
                elif yF1-12*sqrBox >= yClick > yF1 -13*sqrBox:
                    yNum = 100
                elif yF1-13*sqrBox >= yClick > yF1 -14*sqrBox:
                    yNum = 50
                else:
                    yNum = 0
                
                chosenColor = colorList[xNum+yNum]
                break
                        
    label.undraw()
    label = g.Text(g.Point(frame.getCenter().getX(),50),chosenColor)
    label.setStyle('bold'); label.setSize(26)
    label.draw(win)            
    colorBox = g.Rectangle(g.Point(xF1,yF1),g.Point(xF2,yF2))
    colorBox.setFill(chosenColor), colorBox.setOutline(chosenColor)
    colorBox.draw(win)
    t.sleep(1)
    win.close()
    return chosenColor
