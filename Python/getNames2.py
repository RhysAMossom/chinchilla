def getNames2():
    print 'Enter name(s) or press ENTER to quit.'
    nameList = []
    name = " "
    while True:
        name = raw_input("Enter Name ")
        if name: # if name !="":
            nameList.append(name)
        else:
            return nameList
getNames2()
