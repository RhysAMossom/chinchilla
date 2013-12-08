def noBdayMatch(people):
    
    if people <=0:
        raise ValueError
    elif people > 365:
        return 0.0
    elif people == 1:
        return 0.0
    elif people == 2:
        return 364.0/365.0
    else:
        return float(noBdayMatch(people-1)*(365.0 + 1 - people)/365)


#testing
print "%15s%17s%17s" %("# People","Prob.Share","Prob.Not.Share")
for i in range(1,366):
    print "%15d%17.7f%17.7f" %(i,1.0-noBdayMatch(i),noBdayMatch(i))
