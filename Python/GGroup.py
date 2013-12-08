import graphics as g

class GGroup(object):
    def __init__(self, anchorPoint):
        self.anchorPoint = anchorPoint
        self.groupList = []

    def __str__(self):
        return "GGroup object with %d elements." %len(self.groupList)

    def addElement(self,element):
        self.groupList.append(element)

    def draw(self, window):
        for element in self.groupList:
            element.draw(window)

    def draw2(self, window):
        for element in self.groupList:
            element.draw2(window)


    def clone(self):
        cloneGroupList = GGroup(g.Point(0,0))
        for element in self.groupList:
            cloneGroupList.addElement(element.clone())
        return cloneGroupList

    def move(self, dx, dy):
        self.anchorPoint.move(dx,dy)
        for element in self.groupList:
            element.move(dx,dy)

    def move2point(self,point):
        oldAnchor = self.anchorPoint
        newAnchor = point
        xNew = newAnchor.getX()
        yNew = newAnchor.getY()
        xOld = self.anchorPoint.getX()
        yOld = self.anchorPoint.getY()
        for element in self.groupList:
            dx = xNew - xOld
            dy = yNew - yOld
            element.move(dx,dy)
        self.anchorPoint = point
        

    def undraw(self):
        for element in self.groupList:
            #try:
                element.undraw()
            #except:
               # continue
            

    
        
