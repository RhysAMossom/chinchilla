import graphics as g
import random as r
def graphStuff():
    win = g.GraphWin("WINDOW",500,400)
    win.setCoords(0.0,0.0,100.0,100.0)
    p = g.Point(50,50)
    cir = g.Circle(g.Point(75,75),10)
    cir.setFill('peachpuff')
    cir.setOutline('LightSalmon2')
    cir.draw(win)
    win.setBackground('peru')
    cir.move(0,20)
    cloneCir = cir.clone()
    cloneCir.draw(win)
    cloneCir.move(-25,-50)
    label = g.Text(g.Point(20.0,85.0),"Ta-Da!")
    label.draw(win)

    p2 = win.getMouse()
    label2 = g.Text(p2,"You clicked here.")
    label2.draw(win)

    p3 = win.getMouse()
    x3 = p3.getX()
    y3 = p3.getY()    
    line1 = g.Line(g.Point(x3-5,y3-5),g.Point(x3+5,y3+5))
    line2 = g.Line(g.Point(x3-5,y3+5),g.Point(x3+5,y3-5))
    line1.draw(win)
    line2.draw(win)


    stars = []
    for i in range(100):
        star = g.Point(r.randrange(600),r.randrange(450))
        star.draw(win)
        stars.append(star)
    p1 = g.Point(300,50)
    p2 = g.Point(200,250)
    p3 = g.Point(500,100)
    p4 = g.Point(100,100)
    p5 = g.Point(400,250)
    fivept = g.Polygon(p1,p2,p3,p4,p5)
    fivept.setFill("pink")
    fivept.draw(win)

    raw_input("Press ENTER to quit.")

if __name__ == "__archery__":
    archery()

    
    raw_input("Press ENTER to quit.\n")
graphStuff()
