import graphics as g
import time as t
from GGroup import *
from inButton import *


def main():
    win = g.GraphWin('Moving Stuff Around', 1000,700)
    group = GGroup(g.Point(50,50))
    print group

    quitButt = g.Rectangle(g.Point(150,480),g.Point(320,430))
    quitButt.setFill('pink');quitButt.setOutline('red')
    quitButt.draw(win)

    quitText = g.Text(quitButt.getCenter(),"Clear & Quit")
    quitText.setSize(26); quitText.setFace('helvetica');quitText.setStyle('bold'); quitText.draw(win)

    circle = g.Circle(g.Point(50,50),5)
    circle2 = g.Circle(g.Point(34,44),52)
    text = g.Text(g.Point(9,20),"WASSAP!")   

    group.addElement(circle)
    print group
    group.addElement(circle2)
    print group  
    group.addElement(text)
    print group

    group.draw(win)

    group2 = group.clone()
    print group2
    group2.addElement(g.Text(g.Point(0,0),'Clone1, Group2'))
    group2.move(500,100)
    group2.draw2(win)

    group3 = group.clone()
    group3.addElement(g.Text(g.Point(0,0),'Clone2, Group3'))
    group3.move(0,300)
    group3.draw2(win)

    first = True
    while True:
        click = win.getMouse()
        if inButton(click,quitButt):
            group.undraw()
            t.sleep(2)
            group2.move(300,300)
            t.sleep(2)
            group3.move(500,-200)
            t.sleep(1)
            win.close()
            break
        elif first:
            group.move(50,50)
            first = False
        else:
            group.move2point(click)

main()
