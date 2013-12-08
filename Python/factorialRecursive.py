def factorialRecursive(n):
    if n == 0:
        return 1# Base Case
    if n <0:
        raise ValueError
    else:
        return n*factorialRecursive(n-1) #Recursive Step
    #This comes back to call the function again, and again, until it gets an answer
    #and returns it to the mother function, which returns it to its mother function
    #until the factorialRecursive(n) is found.
