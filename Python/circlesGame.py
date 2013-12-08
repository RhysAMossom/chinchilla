import graphics as g
import random as r
import time as t
import string as s

def cleanTextFile():
    fh = open('listPythonColorsUNCLEAN.txt','r')
    rawText = fh.read()
    fh.close()
    
    index = rawText.find('AliceBlue')
    rawText = rawText[index:]
    rawText = rawText.replace('  ','*')
    rawText = rawText.replace("\\",'*')
    rawText = rawText.replace("}",'')
    for i in range(10):
        rawText= rawText.replace(' '+str(i),'*')
    for x in range(5):
        for i in range(10):
            rawText = rawText.replace('*'+str(i),'*')
    rawText = rawText.replace("*",'')
    rawText = rawText.replace("\n",'*')
    rawText = s.join(rawText,'')
    rawText = s.split(rawText,"*")
    rawText = rawText[:-1]
    return rawText
colorList = cleanTextFile()

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

def main():
# Input Boxes
    print "Grabbing weapons..."
    win = g.GraphWin("Give a round of applause to the CIRCLES GAME!", 600,600)
    win.setBackground('gray50')
    sizeBox = g.Entry(g.Point(250,50),5)
    sizeText = g.Text(g.Point(150,50),"Radius Size:")
    sizeText.setStyle('bold'); sizeText.setSize(17)
    sizeBox.draw(win);sizeText.draw(win)

    numBox = g.Entry(g.Point(250,100),5)
    numText = g.Text(g.Point(120,100),"Number of Circles:")
    numText.setStyle('bold'); numText.setSize(17)
    numBox.draw(win); numText.draw(win)

# Buttons
    drawButton = g.Rectangle(g.Point(300,100),g.Point(400,50))
    drawText = g.Text(drawButton.getCenter(),"Draw")
    drawButton.setFill('black'); drawText.setFill('white')
    drawText.setStyle('bold'); drawText.setSize(24)
    drawButton.draw(win); drawText.draw(win)

    quitButton = drawButton.clone(); quitButton.move(150,30)
    quitText = g.Text(quitButton.getCenter(),"Quit")
    quitButton.setFill('black'); quitText.setFill('white')
    quitText.setStyle('bold'); quitText.setSize(24)
    quitButton.draw(win); quitText.draw(win)

    clearButton = drawButton.clone(); clearButton.move(150,-30)
    clearText = g.Text(clearButton.getCenter(),"Clear")
    clearButton.setFill('black'); clearText.setFill('white')
    clearText.setStyle('bold'); clearText.setSize(24)
    clearButton.draw(win); clearText.draw(win)
    circle = g.Circle(g.Point(0,0),1)

# Drawing and Input
    frame = g.Rectangle(g.Point(10,590),g.Point(590,150))
    frame.draw(win)
    played =0
    print "\nGame armed to the toes.\n\nGO GET'em TIGER!\n"
    while True:
        click = win.getMouse()
        if inButton(click,quitButton):
            sizeBox.undraw();numBox.undraw();numText.undraw();sizeText.undraw();clearText.undraw()
            quitButton.undraw();quitText.undraw();drawButton.undraw(); drawText.undraw();clearButton.undraw()
            GOtext = g.Text(g.Point(300,75),"You Killed It!")
            GOtext.setSize(36); GOtext.setStyle('bold');GOtext.setFill('white')
            GOtext.draw(win)
            t.sleep(1)
            win.close()
            break
        elif played and inButton(click,clearButton):
               clearBox = g.Rectangle(g.Point(10,590),g.Point(590,150))
               clearBox.setFill('gray50');clearBox.draw(win)
               sizeBox.setText(""); numBox.setText("")
            
        elif inButton(click,drawButton):
            try:
                numCircles = int(numBox.getText())
                radius = int(sizeBox.getText())
                assert 10000 >=numCircles >0 and 220 >radius >0
            except:
                sizeBox.undraw();numBox.undraw();numText.undraw();sizeText.undraw();clearButton.undraw();clearText.undraw()
                quitButton.undraw();quitText.undraw();drawButton.undraw(); drawText.undraw()
                errorMsg = g.Text(g.Point(300,75),"Invalid Input.\n Size must be an integer between 1 and 219,\n and the number of circles must be\na positive integer no larger than 10,000.")
                errorMsg.setFill('white'); errorMsg.setSize(16)
                errorMsg.draw(win)
                t.sleep(3)
                errorMsg.undraw()
                sizeBox.draw(win);numBox.draw(win);numText.draw(win);sizeText.draw(win);clearButton.draw(win);clearText.draw(win)
                quitButton.draw(win);quitText.draw(win);drawButton.draw(win); drawText.draw(win)
                sizeBox.setText(""); numBox.setText("")
                continue

            sizeBox.undraw();numBox.undraw();numText.undraw();sizeText.undraw();clearButton.undraw();clearText.undraw()
            quitButton.undraw();quitText.undraw();drawButton.undraw(); drawText.undraw()
            drawingText = g.Text(g.Point(300,75),"Drawing...");drawingText.setFill('light blue')
            drawingText.setSize(24); drawingText.draw(win)

            for i in range(numCircles):
                circle = g.Circle(g.Point(r.randrange(10+radius,590-radius),r.randrange(150+radius,590-radius)),radius)
                circle.setFill(r.choice(colorList));circle.setOutline(r.choice(colorList))
                circle.draw(win)
            played = 1
            drawingText.undraw();sizeBox.draw(win);numBox.draw(win);numText.draw(win)
            sizeText.draw(win);clearButton.draw(win);clearText.draw(win)
            quitButton.draw(win);quitText.draw(win);drawButton.draw(win); drawText.draw(win)
            

            
        

    print "Game assassinated.\n"
if __name__ == "__main__":
    main()

    
