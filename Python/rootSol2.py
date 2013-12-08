import math as m
def rootSol2(a,b,c):
    discr= b**2.0 -(4*a*c)
    print a,"x^2 +",b,"x +",c,"= 0"
    print

    try:
        droot = m.sqrt(discr)
        assert droot != 0 #give a condition that is true if droot == 0 we get AssertionErro
    except ValueError: #if you get a ValueError in the try block, do this:
        print "No real roots."
    except AssertionError:
        print "The only solution x =", -b/(2.0*a)
    else:
        print "x1 =", (-b+math.sqrt(discr))/(2.0*a)
        print "x2 =", (-b-math.sqrt(discr))/(2.0*a)
    print
