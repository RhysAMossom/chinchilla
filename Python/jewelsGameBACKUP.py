import graphics as g
import time as t
from GGroup import *
from inButton import *
import random as r
from randExcept import *
from drawOnBoard import *


def checkRight(x,y,dictionary):
    if dictionary[str(x)+str(y)] == dictionary[str(x+1)+str(y+1)]:
        return True
    else:
        return False
    

def main():
    
    # Creating Joyas                                                                                           
    joyas = ['star','circle','square','triangle','rombus','X']

    star = g.Polygon(g.Point(0,-25),g.Point(-25,25),g.Point(30,-5),g.Point(-30,-5),g.Point(25,25))
    star.setFill('orange')
    starG = GGroup(g.Point(0,0)); starG.addElement(star)

    circle = g.Circle(g.Point(0,0),32); circle.setFill('blue'); circle.setOutline('yellow')
    circleG = GGroup(g.Point(0,0)); circleG.addElement(circle)

    square = g.Rectangle(g.Point(-32,-32),g.Point(32,32)); square.setFill('dark green'); square.setOutline('white')
    squareG = GGroup(g.Point(0,0)); squareG.addElement(square)


    triangle = g.Polygon(g.Point(-26,29),g.Point(26,29),g.Point(0,-29))
    triangle.setFill('pink'); triangle.setOutline('red')
    triangleG = GGroup(g.Point(0,0)); triangleG.addElement(triangle)

    rombus = g.Polygon(g.Point(-32,0),g.Point(0,32),g.Point(32,0),g.Point(0,-32))
    rombus.setFill('beige'); rombus.setOutline('purple')
    rombusG = GGroup(g.Point(0,0)); rombusG.addElement(rombus)

    equis = g.Text(g.Point(0,0),'X'); equis.setFill('white'); equis.setStyle('bold'); equis.setSize(36)
    equisG = GGroup(g.Point(0,0)); equisG.addElement(equis)

    # Create Window and Tools
    winW = 820
    winH= 670
    
    win = g.GraphWin('Jewels', winW,winH)
    win.setBackground("dodger blue")
    groupTools = GGroup(g.Point(int(winW/2),int(winH/2)))

    print groupTools###############################################################################################

    quitButt = g.Rectangle(g.Point(winW-100,50),g.Point(winW-10,10))
    quitButt.setFill('pink');quitButt.setOutline('red')
    groupTools.addElement(quitButt)

    quitText = g.Text(quitButt.getCenter(),"Quit")
    quitText.setSize(26); quitText.setFace('helvetica');quitText.setStyle('bold')
    groupTools.addElement(quitText)
    
    gameTitle = g.Text(g.Point(int(winW/2),50), "Joyas")
    gameTitle.setSize(36); gameTitle.setFace('helvetica');gameTitle.setStyle('bold')
    groupTools.addElement(gameTitle)

    # Create Frame
    frame = g.Rectangle(g.Point(10,winH-10),g.Point(winW-10,100))
    frame.setFill("SpringGreen")
    groupTools.addElement(frame)

    # Frame line Vertical
    x = 10
    increase  = 80
    x += increase
    while x < winW:
        line = g.Line(g.Point(x,winH-10),g.Point(x,100))
        groupTools.addElement(line)
        print groupTools##############################################################################################
        x += increase

    # Frame line Horizontal
    y = 100
    y += increase
    while y < winH:
        line = g.Line(g.Point(10,y),g.Point(winW-10,y))
        groupTools.addElement(line)
        print groupTools##############################################################################################
        y += increase

    print groupTools##############################################################################################

    groupTools.draw(win)

    # Create Board
    board = {}
    for x in range(1,11):
        for y in range(1,8):
            joya = r.choice(joyas)
            board[str(x)+str(y)] = joya
            
            while True:
                repeatX = repeatY = False
                if x > 2:
                    if (board[str(x)+str(y)] == board[str(x-1)+str(y)] and board[str(x)+str(y)] == board[str(x-2)+str(y)]):
                        repeatX = False
                        repeatY = True
                    else:
                        repeatY = False
                        
                    while (board[str(x)+str(y)] == board[str(x-1)+str(y)] and board[str(x)+str(y)] == board[str(x-2)+str(y)]):
                        board[str(x)+str(y)] = randExcept(joyas,board[str(x)+str(y)])
                    
        
                if y > 2:
                    if (board[str(x)+str(y)] == board[str(x)+str(y-1)] and board[str(x)+str(y)] == board[str(x)+str(y-2)]):
                        repeatX = True
                        repeatY = False
                    else:
                        repeatX = False
                        
                    while (board[str(x)+str(y)] == board[str(x)+str(y-1)] and board[str(x)+str(y)] == board[str(x)+str(y-2)]):
                        board[str(x)+str(y)] = randExcept(joyas,board[str(x)+str(y)])
                    
                    
                if repeatX or repeatY:
                    continue
                else:
                    break
                
    print board,"Length = ", len(board)##############################################################################################

    #Draw Board
    boardObjects = {}
    for x in range(1,11):
        for y in range(1,8):
            joya = board[str(x)+str(y)]
            if joya == 'star':
                boardObjects[str(x)+str(y)] = starG.clone()
            elif joya == 'circle':
                boardObjects[str(x)+str(y)] = circleG.clone()
            elif joya == 'square':
                boardObjects[str(x)+str(y)] = squareG.clone()
            elif joya == 'triangle':
                boardObjects[str(x)+str(y)] = triangleG.clone()
            elif joya == 'rombus':
                boardObjects[str(x)+str(y)] = rombusG.clone()
            else:
                boardObjects[str(x)+str(y)] = equisG.clone()
            boardObjects[str(x)+str(y)].move(10+(increase/2)+(increase*(x-1)),100+(increase/2)+(increase*(y-1)))
            boardObjects[str(x)+str(y)].draw2(win)
    


    
    # getting clicks
    one = True

    while True:
        click = win.getMouse()

        # Quitting
        if inButton(click,quitButt):
            groupTools.undraw()
            t.sleep(1)
            for joya in boardObjects.values():
                joya.undraw()
                t.sleep(0.02)
            win.close()
            break
        # Check for clicks inside Fram
        elif not inButton(click,frame):
            continue
        else:

            # First Click
            if one:
                click1 = click
                x1 = 1+(click1.getX()-10)/increase
                y1 = 1+(click1.getY()-100)/increase

                print "X1",x1,"Y1",y1##############################################################################################

                one = False
                boardObjects[str(x1)+str(y1)].undraw()
                square1 =g.Rectangle(g.Point(10+((x1-1)*increase),100+((y1-1)*increase)),g.Point(10+increase+((x1-1)*increase),100+increase+((y1-1)*increase)))
                square1.setFill('red')
                square1.draw(win)
                boardObjects[str(x1)+str(y1)].draw2(win)

            else: # Second Click
                click2 = click
                x2 = 1+(click2.getX()-10)/increase
                y2 = 1+(click2.getY()-100)/increase

                print "X2",x2,"Y2",y2##############################################################################################
                if (((x2-x1)**2)**0.5 + ((y2-y1)**2)**0.5) !=1:
                    print "ERROR: Equal click or distanced box."##############################################################################################
                    continue

                boardObjects[str(x2)+str(y2)].undraw()
                square2 =g.Rectangle(g.Point(10+((x2-1)*increase),100+((y2-1)*increase)),g.Point(10+increase+((x2-1)*increase),100+increase+((y2-1)*increase)))
                square2.setFill('blue')
                square2.draw(win)
                boardObjects[str(x2)+str(y2)].draw2(win)

                one = True

            #Check for Matching Jewels (three in a row)
                if board[str(x2)+str(y2)]==board[str(x1)+str(y1)]:
                    t.sleep(0.5)
                    square1.setFill('blue');square2.setFill('red')
                    t.sleep(1)
                    square1.setFill('red');square2.setFill('blue')
                    
                    print "Equal jewels"##############################################################################################
            # Change jewels places
                else:
                    square1.setFill('blue');square2.setFill('red')
                    
                    joyaTemp = board[str(x1)+str(y1)]
                    board[str(x1)+str(y1)] = board[str(x2)+str(y2)]
                    board[str(x2)+str(y2)] = joyaTemp

                    listPointsXY = [x1,y1,x2,y2]
                    for i in range(0,1+len(listPointsXY)/2,2):
                        x = listPointsXY[i]
                        y = listPointsXY[i+1]
                        boardObjects[str(x)+str(y)].undraw()
                        
                    print "ReDrawing Board"##############################################################################################                            
                    boardObjects = drawOnBoard(win,listPointsXY,board,starG,circleG,squareG,triangleG,rombusG,equisG,increase,boardObjects)
                    print "DONE ReDrawing"############################################################################################## 

                    # Check if Move makes a match
                    matches = True
                    while matches:
                        matchX = matchY = False
                        if not matches:
                            print "NO MATCH"
                        # Re-draw Board
                            listPointsXY = [x1,y1,x2,y2]
                            t.sleep(1)
                            for i in range(0,1+len(listPointsXY)/2,2):
                                x = listPointsXY[i]
                                y = listPointsXY[i+1]
                                boardObjects[str(x)+str(y)].undraw()

                            square1.setFill('red');square2.setFill('blue')
                            joyaTemp = board[str(x1)+str(y1)]
                            board[str(x1)+str(y1)] = board[str(x2)+str(y2)]
                            board[str(x2)+str(y2)] = joyaTemp
                           
                            boardObjects = drawOnBoard(win,listPointsXY,board,starG,circleG,squareG,triangleG,rombusG,equisG,increase,boardObjects)
                            t.sleep(1)
                            break
                        
                        for x in range(1,11):
                            for y in range(1,8):                                                           
                                
                                print "INSIDE LOOP"
                                if x > 2:
                                    if (board[str(x)+str(y)] == board[str(x-1)+str(y)] and board[str(x)+str(y)] == board[str(x-2)+str(y)]):
                                        matchX = True
                                        print "Horizontal Match." ###############################################################
                                        board[str(x)+str(y)] = r.choice(joyas)
                                        board[str(x-1)+str(y)] = r.choice(joyas)
                                        board[str(x-2)+str(y)] = r.choice(joyas)

                                        # Re-draw Board
                                        listPointsXY = [x,y,x-1,y,x-2,y]
                                        for i in range(0,1+len(listPointsXY)/2,2):
                                            x = listPointsXY[i]
                                            y = listPointsXY[i+1]
                                            boardObjects[str(x)+str(y)].undraw()
                                        boardObjects = drawOnBoard(win,listPointsXY,board,starG,circleG,squareG,triangleG,rombusG,equisG,increase,boardObjects)
                                                                                    
                                if y > 2:
                                    if (board[str(x)+str(y)] == board[str(x)+str(y-1)] and board[str(x)+str(y)] == board[str(x)+str(y-2)]):
                                        matchY = True
                                        print "Vertical Match." ###############################################################
                                        board[str(x)+str(y)] = r.choice(joyas)
                                        board[str(x)+str(y-1)] = r.choice(joyas)
                                        board[str(x)+str(y-2)] = r.choice(joyas)
                                        # Re-draw Board
                                        listPointsXY = [x,y,x,y-1,x,y-2]
                                        for i in range(0,1+len(listPointsXY)/2,2):
                                            x = listPointsXY[i]
                                            y = listPointsXY[i+1]
                                            boardObjects[str(x)+str(y)].undraw()
                                        boardObjects = drawOnBoard(win,listPointsXY,board,starG,circleG,squareG,triangleG,rombusG,equisG,increase,boardObjects)
                                
                                        

                                if matchX and matchY:
                                    print "Double Match: vertical and horizontal." ###############################################################
                                    continue
                                elif matchX or matchY:
                                    print "Single Match." ###############################################################
                                    continue
                                else:
                                    
                                    matches = False
                                    break
                    
                    
                    
                    print "out of loop"##############################################################################################
                    
                t.sleep(0.5)
                square1.undraw();square2.undraw()
            continue

main()
