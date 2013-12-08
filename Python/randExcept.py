import random as r
def randExcept(nameList,exception):
    if len(nameList) < 2:
        print "List cannot consist of one or less elements."
        raise ValueError
    choice = exception
    
    while choice == exception:
        choice = r.choice(nameList)
    

    return choice
