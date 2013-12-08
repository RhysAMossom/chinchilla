def getCoeffs2():
    # Coeff for a
    while True:
        try:
            a = float(raw_input("Enter value of a:   "))
            assert (5.<= a <=10.0)
        except ValueError:
            print "Not a valid number."
            continue
        except AssertionError:
            print "Not not in range [5,10]."
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
