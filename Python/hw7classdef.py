import graphics as g

class GGroup(object):
    def __init__(self, anchorPoint):
        """
        defines the anchorpoint as 'self.anchorpoint' so that
        all the other methods can make use of it.
        Also creates an empty list to store all the element variable names.
        """
        
        self.anchorPoint=anchorPoint
        self.elements=[]
        
    def __str__(self):
        """
        just tells us how many elements (or objects) are in the list
        """
        
        return "GGroup object with %d elements" %(len(self.elements))
        
    def addElement(self,element):
        """
        adds the object to the list of elements.
        *note*: can probably be made better bychecking whether or not the
        element to be added already exists in the list, to avoid duplicates
        """
        
        self.elements.append(element)

    def draw(self,window):
        """
        will take every element in the list, and draw it in the
        window specified in the argument
        """
                
        for i in self.elements:
            i.draw(window)

    def move(self,dx,dy):
        """
        will use the 'move()' method specified in the graphics.py library.
        *note* since the elements are objects created with the graphics.py library,
        the .move() method from that  library is used to 'move' them.  this allows us
        to not have to define an entirely new move() method for our GGroup, since every
        element (point, circle, text, line etc.) already has a move method defined in
        the graphics.py library.
        """
                
        self.anchorPoint.move(dx,dy)
        for i in self.elements:
            i.move(dx,dy)

    def undraw(self):
        """
        same deal with .undraw().  there is already an undraw() method defined
        in the graphics.py library for all of these elements, so we need not re-invent
        the wheel to move our entire group.
        """

        for i in self.elements:
            i.undraw()
        
            
