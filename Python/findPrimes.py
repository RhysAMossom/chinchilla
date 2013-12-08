from factors import *

def findPrimes(n):
    primeList = []
    for i in range(1,n+1):
        tempList = factors(i)
        if len(tempList) == 2:
            primeList.append(i)
    return primeList
