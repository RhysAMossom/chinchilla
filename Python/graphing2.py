import graphics as g
def graphing2():
    win1 = g.GraphWin("My window 1",500,400)
    p1 = g.Point(50,50)
    cir1 = g.Circle(g.Point(75,75),10)
    cir1.setFill('peachpuff')
    cir1.setOutline('LightSalmon2')
    cir1.draw(win1)
#    win1.setBrackground('peru')

    raw_input("Press ENTER to continue.\n")
    
  
    win2 = g.GraphWin("My window 2",500,400)
    win2.setCoords(0.0,0.0,100.0,100.0)
    p2 = g.Point(50,50)
    cir2 = g.Circle(g.Point(75,75),10)
    cir2.setFill('pink')
    cir2.setOutline("limegreen")
    cir2.draw(win2)

    raw_input("Press ENTER to quit.\n")
graphing2()
