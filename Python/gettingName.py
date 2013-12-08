import graphics as g

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

def gettingName():
    winName = g.GraphWin('Archery Enter Name',400,100)
    winName.setBackground('light blue')

    OKbutt = g.Rectangle(g.Point(310,90),g.Point(390,10))
    OKbutt.setFill('pink');OKbutt.setOutline('red')
    OKbutt.draw(winName)

    OKtext = g.Text(OKbutt.getCenter(),"Join")
    OKtext.setSize(24);OKtext.setStyle('bold'); OKtext.draw(winName)
    
    hallOF= g.Text(g.Point(150,20),"Join others in the Hall of Fame")
    hallOF.setFill('purple');hallOF.setStyle('bold');hallOF.setSize(18)
    hallOF.setFace('times roman'); hallOF.draw(winName)

    name = g.Entry(g.Point(150,60),20)
    name.setText("Enter your Name");name.draw(winName)
    newName1 = ''
    while True:
        click2 = winName.getMouse()
        if inButton(click2,OKbutt):
            newName1 = name.getText()
            newName1 = newName1.replace(' ','')
        else:
            continue
        if newName1 == '' or len(newName1)>10:
            hallOF.undraw()
            hallOF= g.Text(g.Point(150,20),"Name must be between\n 1 and 10 characters")
            hallOF.setFill('red');hallOF.setStyle('bold');hallOF.setSize(14)
            hallOF.setFace('times roman'); hallOF.draw(winName)

            continue
        else:
            break
    print newName1
gettingName()
