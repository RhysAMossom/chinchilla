def syracuseSeq2(number):
    sequence = str(number)
    length = 1
    while number != 1:
        if number%2 == 0:
            number = number /2
        else:
            number = 3*number +1
        sequence= sequence +" "+str(number)
        length += 1
    print
    print "Hailsonte Sequence:"
    print sequence
    print
    print "The lenght of the sequence is: ", length
    print
