import math
def rootSol():
    a,b,c = input("Enter 3 numbers separated by commas   ")
    discr= b**2.0 -(4*a*c)
    print a,"x^2 +",b,"x +",c,"= 0"
    print

    if discr < 0:
        print "No real solution"
    elif discr == 0:
        print "The only solution is", (-b/(2.0*a))
    else:
        print "x1 =", (-b+math.sqrt(discr))/(2.0*a)
        print "x2 =", (-b-math.sqrt(discr))/(2.0*a)
    print
rootSol()
