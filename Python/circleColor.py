import graphics as g
import random as r

def main():
    colorList = ['red','blue','green','pink','purple','yellow']
    win = g.GraphWin("Click in Circle", 500,500)
    
    radius = 50
    xCenter = 250
    yCenter = 250
    circle = g.Circle(g.Point(xCenter,yCenter),radius)
    circle.setFill('black');circle.draw(win)

    while True:
        click = win.getMouse()
        x = click.getX()
        x += -xCenter
        y = click.getY()
        y += -yCenter
           
        dist = (x**2 + y**2)**0.5

        print 'x', x, 'y',y, 'distance', dist
        if dist <= radius:
            color = r.choice(colorList)
            circle.setFill(color)
            print color
            
            win.update()
        else:
            win.setBackground('black')
            break

    raw_input("ENTER to quit.")

main()
            
        
    
