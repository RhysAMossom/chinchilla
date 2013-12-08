import graphics as g
import random as r
import time as t

def inCircle(pt,circle):
    xCenter = circle.getCenter().getX()
    yCenter = circle.getCenter().getY()
    radius = circle.getRadius()

    x = pt.getX()
    x += -xCenter
    y = pt.getY()
    y += -yCenter
       
    dist = (x**2 + y**2)**0.5

    if dist <= radius:
        return True
    else:
        return False          
        

def main():
    w = g.GraphWin("Bounce...",600,600)
    w.setCoords(-0.1,-0.1,1.1,1.1)

    box = g.Rectangle(g.Point(0.0,0.0),g.Point(1.0,1.0))
    box.draw(w)

    startpt = g.Point(r.uniform(0.05,0.95),r.uniform(0.05,0.95))

    ball = g.Circle(startpt, 0.03)
    ball.setFill('green')
    ball.draw(w)

    xvel = r.random()/100.0
    yvel = r.random()/100.0

    for i in range(1000):
        ball.move(xvel,yvel)
        x = ball.getCenter().getX()
        y = ball.getCenter().getY()
        if x >= 0.97 or x <= 0.03:
            xvel = -xvel
        if y >= 0.97 or y <= 0.03:
            yvel = -yvel
        
        w.update()
        t.sleep(0.02)
        


    raw_input("<ENT> to quit.")

if __name__=='__main__':
    main()
