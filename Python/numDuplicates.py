def numDuplicates(nameList):
    duplicates = []
    num = 0
    for i in range(len(nameList)):
        if nameList[i] in nameList[i+1:]:
            num +=1
            duplicates.append(nameList[i])
            if not(nameList[i] in duplicates):
                duplicates.append(nameList[i])
    return num,duplicates
