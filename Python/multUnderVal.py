def multUnderVal(mult,lim):
    count = 0
    for x in range(0,lim,mult):
        count += x #this is the same as "count = count + x"
    return count
