def drawOnBoard(win,listPointsXY,board,starG,circleG,squareG,triangleG,rombusG,equisG,increase,boardObjects):
    for i in range(0,1+len(listPointsXY)/2,2):
        x = listPointsXY[i]
        y = listPointsXY[i+1]

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
    return boardObjects
