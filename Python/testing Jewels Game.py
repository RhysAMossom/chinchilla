import graphics as g
from GGroup import *

def main():
    win = g.GraphWin("d",500,500)

    star = g.Polygon(g.Point(30,0),g.Point(5,50),g.Point(60,20),g.Point(0,20),g.Point(55,50))
    star.setFill('orange')
    starG = GGroup(g.Point(0,0)); starG.addElement(star)
    starG.draw(win)

    circle = g.Circle(g.Point(0,0),36); circle.setFill('blue'); circle.setOutline('blue')
    circleG = GGroup(g.Point(0,0)); circleG.addElement(circle)
    circleG.draw(win)

    square = g.Rectangle(g.Point(0,0),g.Point(76,76)); square.setFill('dark green'); square.setOutline('dark green')
    squareG = GGroup(g.Point(0,0)); squareG.addElement(square)
    squareG.draw(win)


    triangle = g.Polygon(g.Point(0,58),g.Point(74,58),g.Point(37,0))
    triangle.setFill('pink'); triangle.setOutline('pink')
    triangleG = GGroup(g.Point(0,0)); triangleG.addElement(triangle)
    triangleG.draw(win)

    rombus = g.Polygon(g.Point(36,72),g.Point(0,36),g.Point(36,0),g.Point(72,36))
    rombus.setFill('beige'); rombus.setOutline('beige')
    rombusG = GGroup(g.Point(0,0)); rombusG.addElement(rombus)
    rombusG.draw(win)

    equis = g.Text(g.Point(40,40),'X'); equis.setFill('white'); equis.setStyle('bold'); equis.setSize(36)
    equisG = GGroup(g.Point(0,0)); equisG.addElement(equis)
    equisG.draw(win)
main()
