import graphics as g

def graphingWin():
    window = g.GraphWin("Python is so much fun!", 500,500)
    p = g.Point(100,100)
    p.draw(window)
    c = g.Circle(p,75)
    c.setFill('red')
    c.draw(window)
    p2 = window.getMouse()
    c2= g.Circle(p2,177)
    c2.setFill('peachpuff')
    c2.setOutline('peachpuff')
    c2.draw(window)

    for radius in range(10,200,20):
        px = window.getMouse()
        cx = g.Circle(px,radius)
        cx.setFill('cyan')
        cx.draw(window)

        
    raw_input("Press ENTER to quit.")
graphingWin()
