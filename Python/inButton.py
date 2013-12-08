def inButton(pt,button):
    x = pt.getX()
    y = pt.getY()

    x1 = button.getP1().getX()
    x2 = button.getP2().getX()
    y1 = button.getP1().getY()
    y2 = button.getP2().getY()

    top = min([y1,y2])
    bottom = max([y1,y2])
    left = min([x1,x2])
    right = max([x1,x2])

    if (bottom > y > top and left < x < right):
        return True
    else:
        return False
