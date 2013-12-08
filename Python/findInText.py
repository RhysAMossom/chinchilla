def findInText():
    text ="Hello how r you doing bla bla this is a jorge . jorge can be very long and contain a lot of charachters. jorge ."
    result = []
    searchFor = "jorge"
    index = text.find(searchFor)

    print text+'\n\n'
    if index == -1:
        print searchFor,"not found in text." 
        return
    else:
        print "Starting at index",index,"there is", text[index:index+1+len(searchFor)]
    
    while index != (-1) and index != (len(text)-1):#checks that the string is not the in the last index
        print "Appending index", index
        result.append(index)
        newindex = text[(index+1):].find(searchFor)
        if newindex == -1:
            break
        index += (newindex + 1)
        print "Starting at index",index,"there is", text[index:index+1+len(searchFor)]
    return result

findInText()
