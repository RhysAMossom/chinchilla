def numPlays():
    while True:
        try:
            plays = int(raw_input("How many times would you like to play?   "))
            assert plays > 0
        except AssertionError:
            print "You cannot play", plays, "times!"
            print
        except ValueError:
            print "That's not a positive integer at all."
            print
        else:
            print "You are playing", plays,"times."
            print
            break
    for numGame in range(plays):
        string = raw_input("Type in random word #" + str(numGame+1) + ": ")
        if len(string)%2 == 0:
            msg = 'The string "'+ string +'" has no middle character.'
        
        elif len(string) == 1:
            if string == ' ':
                msg = "You entered a space."
            else:
                msg = "Your one-character string is: "+ string
        else:
            midChar = string[(len(string)+1)/(-2)]
            if midChar == ' ':
                msg = 'The middle character of the string "'+ string +'" is a space.'
            else:
                msg = 'The middle character of the string "'+ string +'" is "'+ midChar +'".'
        print msg
        print
    print
    
numPlays()
