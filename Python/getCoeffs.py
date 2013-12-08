def getCoeffs():
    # Coeff for a
    while True:
        try:
            a = float(raw_input("Enter value of a:   "))
        except ValueError:
            print "Not a valid number."
            continue
        else:
            break
    #Coeff for b
    while True:
            try:
                b = float(raw_input("Enter value of b:   "))
            except ValueError:
                print "Not a valid number."
                continue
            else:
                break
    #Coeff for c
    while True:
            try:
                c = float(raw_input("Enter value of c:   "))
            except ValueError:
                print "Not a valid number."
                continue
            else:
                break
    print        
    return a, b, c
