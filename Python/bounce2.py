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
    radius = 30 #pixels
    width = 1000
    height = 600

    w = g.GraphWin("Bounce...",width,height)

    
    box = g.Rectangle(g.Point(radius,height-radius),g.Point(width-radius,radius))
    box.draw(w)

    startpt = g.Point(r.randint(2*radius,width-(2*radius)),r.randint(2*radius,height-(2*radius)))

    ball = g.Circle(startpt, radius)
    ball.setFill('green'); ball.setOutline('green')
    ball.draw(w)

    xvel = r.randint(1,3)
    yvel = r.randint(1,3)
    while True:
        #click = w.getMouse()
        
        
        
    
        ball.move(xvel,yvel)
        x = ball.getCenter().getX()
        y = ball.getCenter().getY()
        if x >= width - (2*radius) or x <= 2*radius:
            xvel = -xvel
            ball.setFill('blue')
        if y >= height - (2*radius) or y <= 2*radius:
            yvel = -yvel
            ball.setFill('green')
##        if inCircle(click,ball):
##            ball.setFill('pink')
##        else:
##            w.setBackground('black')
##            break

        w.update()
        t.sleep(0.02)
        


    raw_input("<ENT> to quit.")

if __name__=='__main__':
    main()
