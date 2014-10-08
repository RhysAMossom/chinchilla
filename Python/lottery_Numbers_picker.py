#! /usr/bin/env python
from itertools import permutations
import csv

def permutate(n):
    return ['%s%s%s' % (p[0],p[1],p[2]) for p in permutations(n)]

def unique_digits(n):
    for d in n:
        for i in n[n.index(d)+1:]:
            if d == i:
                return False
    return True

if "__main__" == __name__:
    distinct_numbers_unique_digits =[]
    distinct_numbers = []
    covered_for = []
    
    with open("lottery_numbers.csv","w") as fh:
        numbers = {'number':None,'buy':None,'sum':None,'buy sum':None}
        log_file = csv.DictWriter(fh, numbers.keys(), extrasaction='ignore')
        log_file.writeheader()
        
        for number in range(1000):
            n = "%.3d" % number
            if n in covered_for:
              continue
            else:
                distinct_numbers.append(n)
                if unique_digits(n):
                    distinct_numbers_unique_digits.append(n)
                for p in permutate(n):
                    if p not in covered_for:
                        covered_for.append(p)
    
    print("%d distinct numbers" % len(distinct_numbers))
    print("chances of getting a distinct number: %.2f" %(len(distinct_numbers)/1000.0))
    #print(distinct_numbers)
    print("%d distinct numbers with unique digits" % len(distinct_numbers_unique_digits))
    print("chances of getting a distinct number with unique digits: %.2f" %(len(distinct_numbers_unique_digits)/1000.0))
    #print(distinct_numbers_unique_digits)
    print("chossing distinct numbers cover for %d other numbers" % len(covered_for))


# To do: 
# * get stats on existing numbers
