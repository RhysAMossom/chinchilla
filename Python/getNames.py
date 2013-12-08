def getNames():
    numNames = raw_input("How many names do you want to type? ")
    print
    nameList = []
    for ind in range(int(numNames)):
        tempName = raw_input("Enter Name ")
        nameList.append(tempName)
    return nameList
getNames()
