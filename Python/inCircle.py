import graphics as g

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
        
    
