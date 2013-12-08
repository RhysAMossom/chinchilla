def factors(n):
    """
    Takes a positive integer n.
    Returns a list of its positive factors.
    """
    if type(n) != type(0) or n <1:
        raise ValueError

    factorList = []
    for i in range(1,n+1):
        if n%i == 0:
            factorList.append(i)

    return factorList
