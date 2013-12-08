import graphics as g
import hw7classdef as hw7


win=g.GraphWin('mywindow',900,900)
circle=g.Circle(g.Point(25,25),5)
circle2=g.Circle(g.Point(75,75),28)
group=hw7.GGroup(g.Point(50,50))
text=g.Text(g.Point(90,25),'hello world')
group.addElement(circle)
print group

group.addElement(text)
print group

group.addElement(circle2)
print group
group.draw(win)
win.getMouse()
group.move(200,200)
win.getMouse()
group.undraw()
win.getMouse()
