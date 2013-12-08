def numInRange():
    while True:
        try:
            x = int(raw_input("Enter an integer in [-10,10]   "))
            assert -10 <= x <= 10
        except AssertionError:
            print "Number out of range"
        except ValueError:
            print "That's not an integer at all."
        else:
            print "You entered", x
            break
numInRange()
