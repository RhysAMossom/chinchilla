from dateClass import Date

def main():
    count = {}
    while(moreDates()):
        event = nextDate()
        if event in count:
            coutn[event]+=1
        else:
            count[event] = 1
    for day in count:
        print "%-20s%d" %(str(day),count[day])

main()
