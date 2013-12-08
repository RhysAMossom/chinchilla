import graphics as g
import random as r
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
    P1 = button.getP1()
    P2 = button.getP2()
    x1 = P1.getX()
    x2 = P2.getX()
    y1 = P1.getY()
    y2 = P2.getY()

    top = min([y1,y2])
    bottom = max([y1,y2])
    left = min([x1,x2])
    right = max([x1,x2])

    if (bottom > y > top and left < x < right):
        return True
    else:
        return False

def main():
    win = g.GraphWin("Enter Text", 1000,600)
    win.setBackground(r.choice(colorList))
    text = g.Entry(g.Point(100,550),20)
    text.setText("Type something")
    text.draw(win)

    button = g.Rectangle(g.Point(200,550),g.Point(450,595))
    button.setFill('white')
    button.draw(win)
    
    buttonText = g.Text(button.getCenter(),"Click Me!")
    buttonText.setStyle('bold')
    buttonText.draw(win)

    quitButton = g.Rectangle(g.Point(950,550),g.Point(990,595))
    quitButton.setFill('white')
    quitButton.draw(win)
    quitText = g.Text(quitButton.getCenter(),'QUIT')
    quitText.setStyle('bold')
    quitText.draw(win)

    while True:
        click = win.getMouse()
        if inButton(click,button):
            word = text.getText()
            
            for i in range(20):
                place = g.Point(r.randrange(50,950),r.randrange(50,500))
                label = g.Text(place,word)
                label.setFill(r.choice(colorList))
                label.setSize(r.randrange(5,37))#same as r.randchoice(range(5,37))
                label.setFace(r.choice(['helvetica', 'courier', 'times roman','arial']))
                label.setStyle(r.choice(['normal', 'bold', 'italic','bold italic']))
                label.draw(win)
        elif inButton(click, quitButton):
            win.close();break

    print "You killed the program\n\n"

main()
