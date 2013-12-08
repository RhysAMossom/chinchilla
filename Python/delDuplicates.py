def delDuplicates(nameList):
    newList = []
    for i in nameList:
        if not( i in newList):
            newList.append(i)
    return newList
