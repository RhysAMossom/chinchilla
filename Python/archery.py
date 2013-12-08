import graphics as g
import random as r
import time as t

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
    win = g.GraphWin("Archery Game", 1000,500)
    win.setBackground('light blue')
    colorList = ['white','black','blue','red','yellow']
   
# Decoration
    stars = []
    for i in range(100):
        star = g.Point(r.randrange(1000),r.randrange(500))
        star.draw(win)
        stars.append(star)
    rect=g.Rectangle(g.Point(10,40),g.Point(400,10))
    rect.setFill('dark turquoise')
    rect.draw(win)

    title = g.Text(rect.getCenter(),"Super AWESOME Archery Game")
    title.setSize(18)
    title.setStyle('bold')
    title.setFill("white")
    title.draw(win)

    rect2= rect.clone()
    rect2.move(0,110)
    rect2.draw(win)

    topS = g.Text(rect2.getCenter(),"Top Scores")
    topS.setSize(18)
    topS.setFill("white")
    topS.setStyle('bold')
    topS.draw(win)
        
    table = g.Polygon(g.Point(10,150),g.Point(10,300),g.Point(400,300),g.Point(400,150))
    table.draw(win)

# Buttons
    quitButt = g.Rectangle(g.Point(150,480),g.Point(270,430))
    quitButt.setFill('pink');quitButt.setOutline('red')
    quitButt.draw(win)

    quitText = g.Text(quitButt.getCenter(),"QUIT")
    quitText.setSize(26); quitText.setFace('helvetica');quitText.setStyle('bold'); quitText.draw(win)
    quitting = False

    resetButton = g.Rectangle(g.Point(400,120),g.Point(300,150))
    resetButton.setFill('pink');resetButton.setOutline('red')
    resetButton.draw(win)
    resetScores = False

    resetText = g.Text(resetButton.getCenter(),'Reset')
    resetText.setSize(20); resetText.setFace('helvetica')
    resetText.setStyle('bold'); resetText.draw(win)

# Load Top Scores
    fh=open('archeryGameScores.txt','r')
    name1 = fh.readline();score1 = fh.readline()
    name2=fh.readline();score2 = fh.readline()
    name3=fh.readline();score3=fh.readline()
    fh.close()
    name1 = name1.replace('\n',''); score1 = score1.replace('\n','')
    name2 = name2.replace('\n',''); score2 = score2.replace('\n','')
    name3 = name3.replace('\n',''); score3 = score3.replace('\n','')
    highScore = int(score1)

    line1 = g.Text(g.Point(205,175),name1+'   '+score1)
    line1.setSize(20);line1.setStyle('bold');line1.setFace('courier'); line1.draw(win)
    line2 = g.Text(g.Point(205,225),name2+'   '+score2)
    line2.setSize(20);line2.setStyle('bold');line2.setFace('courier'); line2.draw(win)
    line3 = g.Text(g.Point(205,275),name3+'   '+score3)
    line3.setSize(20);line3.setStyle('bold');line3.setFace('courier'); line3.draw(win)
    

# Draw Target
    radius = 225
    centerX = 750
    centerY = 250
    for i in range(len(colorList)):
        circles = g.Circle(g.Point(centerX,centerY),radius)
        circles.setFill(colorList[i])
        circles.setOutline(colorList[i])
        circles.draw(win)
        radius += -50
    
# Get Input and show Score
    score = 0
    scoreText = g.Text(g.Point(200,80),"Your Score:  "+str(score))
    scoreText.setStyle('bold'); scoreText.setFace('helvetica')
    scoreText.setSize(24); scoreText.draw(win)
    X = g.Text(g.Point(centerX,centerY),"X");X.setFill('yellow');X.setSize(22);X.setStyle('bold')
    X.draw(win)
    while True:
        click = win.getMouse()
        px = click.getX()
        py = click.getY()

        if inButton(click,quitButt):
            win.close()
            quitting = True
            break
        elif inButton(click,resetButton):
            win.close()
            winReset = g.GraphWin("Archery Reset Options", 400,100)
            winReset.setBackground('black')
            resetMsg = g.Text(g.Point(200,50),"Scores Erased")
            resetMsg.setStyle('bold'); resetMsg.setSize(30)
            resetMsg.setFill('white');resetMsg.draw(winReset)
            resetScores = True
            break

        distance = ((px-centerX)**2 + (py-centerY)**2)**0.5
        X.undraw()
        X = g.Text(click,"X");X.setFill('green');X.setSize(22);X.setStyle('bold')
        if distance <= 25:
            score += 50
        elif distance <= 75:
            score += 40
        elif distance <= 125:
            score += 30
        elif distance <= 175:
            score += 20
        elif distance <= 225:
            score += 10
        else:
            failText = g.Text(g.Point(centerX,centerY),"FAIL!")
            failText.setSize(36); failText.setStyle('bold')
            failText.draw(win)
            t.sleep(1)
            failText.undraw()
            continue
        X.draw(win)
        scoreText.undraw()
        scoreText=g.Text(g.Point(200,80),"Your Score:  "+str(score))
        scoreText.setStyle('bold'); scoreText.setFace('helvetica')
        scoreText.setSize(24); scoreText.draw(win)

# Quit, check for highest score
    if quitting:
        if score > highScore:
            winName = g.GraphWin('Archery Enter Name',400,100)
            winName.setBackground('light blue')

            OKbutt = g.Rectangle(g.Point(310,90),g.Point(390,10))
            OKbutt.setFill('pink');OKbutt.setOutline('red')
            OKbutt.draw(winName)

            OKtext = g.Text(OKbutt.getCenter(),"Join")
            OKtext.setSize(24);OKtext.setStyle('bold'); OKtext.draw(winName)
            
            hallOF= g.Text(g.Point(150,35),"Join the others in the\nHall of Fame")
            hallOF.setFill('purple');hallOF.setStyle('bold');hallOF.setSize(18)
            hallOF.setFace('times roman'); hallOF.draw(winName)

            name = g.Entry(g.Point(150,70),20)
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
                    hallOF= g.Text(g.Point(150,30),"Name must be between\n 1 and 10 characters")
                    hallOF.setFill('red');hallOF.setStyle('bold');hallOF.setSize(14)
                    hallOF.setFace('times roman'); hallOF.draw(winName)
                    continue
                else:
                    winName.close()
                    break  

            newScore1 = str(score); 
            newScore2 = str(highScore); newName2 = name1
            newScore3 = score2; newName3 = name2
            fh = open('archeryGameScores.txt','w')
            fh.write(newName1+'\n')
            fh.write(newScore1+'\n')
            fh.write(newName2+'\n')
            fh.write(newScore2+'\n')
            fh.write(newName3+'\n')
            fh.write(newScore3+'\n')
            fh.close()
        
        win.close();
        GOwin = g.GraphWin("Archery Game Over",400,400)
        GOwin.setBackground('black')

        GOtext = g.Text(g.Point(200,50),"Game Over")
        GOtext.setFill('white'); GOtext.setSize(36);GOtext.setStyle('bold')
        GOtext.draw(GOwin)

        HOFtext = g.Text(g.Point(200,125),"Hall of Fame")
        HOFtext.setFill('blue'); HOFtext.setSize(30); HOFtext.setStyle('bold')
        HOFtext.draw(GOwin)

        # Re-Load Top Scores
        fh=open('archeryGameScores.txt','r')
        name1 = fh.readline();score1 = fh.readline()
        name2=fh.readline();score2 = fh.readline()
        name3=fh.readline();score3=fh.readline()
        fh.close()
        name1 = name1.replace('\n',''); score1 = score1.replace('\n','')
        name2 = name2.replace('\n',''); score2 = score2.replace('\n','')
        name3 = name3.replace('\n',''); score3 = score3.replace('\n','')
        highScore = int(score1)

        line1 = g.Text(g.Point(205,175),name1+'   '+score1)
        line1.setSize(20);line1.setStyle('bold');line1.setFace('courier')
        line1.setFill('white'); line1.draw(GOwin)
        line2 = g.Text(g.Point(205,225),name2+'   '+score2)
        line2.setSize(20);line2.setStyle('bold');line2.setFace('courier')
        line2.setFill('white'); line2.draw(GOwin)
        line3 = g.Text(g.Point(205,275),name3+'   '+score3)
        line3.setSize(20);line3.setStyle('bold');line3.setFace('courier')
        line3.setFill('white'); line3.draw(GOwin)

        t.sleep(4)
        GOwin.close()
    elif resetScores:
        fh = open('archeryGameScores.txt','w')
        for i in range(3):
            fh.write('GHOST\n0\n')
        fh.close()
        t.sleep(3)
        winReset.close()
        print "Scores Erased...\n"

    print "Game Over."

    
if __name__ == "__main__":
    main()
