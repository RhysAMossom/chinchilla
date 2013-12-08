def strings():
    s = raw_input("Enter Text:  ")
    if len(s) >= 5:
        print "The fifth character is", s[5]
    elif len(s) > 0:
        print "The last characeter is:", s[-1]
    else:
        print "You didn't type anything!"
strings()
