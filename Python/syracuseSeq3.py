def syracuseSeq3():
    number = int(raw_input("Enter a positive integer:   "))
    sequence = str(number)
    length = 1
    print "Hailsonte Sequence:"
    while number != 1:
        if number%2 == 0:
            number = number /2
        else:
            number = 3*number +1
        length += 1
        print number,
    print
    print "The lenght of the sequence is: ", length
    print
syracuseSeq3()
    
