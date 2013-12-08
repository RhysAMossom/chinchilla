def accountTable(startYear, numYears, annualRate, initial):
    curYear = startYear
    balance = initial
    earnInt = 0
    for year in range(0,int(numYears)):
        bal1= balance
        curInt = balance*annualRate
        print "Year:", curYear, "Balance: $", int(balance),"Current Interest: $",int(curInt), "Earned by Interest in year: $",int(earnInt)
        balance = balance + balance*annualRate
        bal2= balance
        curYear = curYear + 1
        earnInt = bal2-bal1
    print   
    print "In", numYears, "years you earned $", int(bal1-initial), "of interest."
    print "That is a lot of money! $$$!"
