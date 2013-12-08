def createOutput():
    print "This program creates a table of squares and square roots."
    print

    while True:
        try:
            number= int(raw_input("Enter a positive integer to which to go:   "))
            assert number > 0
        except ValueError:
            print "Invalid input."
            print
            continue
        except AssertionError:
            print "Invalid input."
            print
            continue
        else:
            break

    while True:
        print
        nameFile = raw_input("Enter the name of the output file desired (less than 8 characters).\n\n     ")
        import string as s
        nameFile = s.replace(nameFile,' ','')
        

        if ".txt" in s.lower(nameFile):
            nameFile = s.replace(s.lower(nameFile),'.txt','')
        nameFile = s.replace(nameFile,'.','')
        
        if len(nameFile) > 8 or nameFile == '':
            print "Invalid input. Type in a name for the output file in less than 8 characters."
            continue
        else:
            nameFile+= '.txt'
            break
    print
    print "The table with the values is in the text file", nameFile    
    fh = open(nameFile,"write")
    fh.write("%-20s%-20s%-20s\n\n"%("X","X Squared","Square Root of X"))
    
    for x in range(1,number+1,1):
        fh.write("%-20d%-20d%-20.3f\n"%(x,x**2,x**0.5))
    fh.close()
    print
createOutput()
