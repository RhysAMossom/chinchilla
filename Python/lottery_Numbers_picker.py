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
    sums = []
    total_cost = 0
    
    with open("lottery_numbers.csv","w") as fh:
        numbers = {'number':None,'buy':None,'sum':None,'buy sum':None,'cost':None}
        log_file = csv.DictWriter(fh, numbers.keys(), extrasaction='ignore')
        log_file.writeheader()
        
        for number in range(1000):
            n = "%.3d" % number
            numbers['number'] = n
            numbers['cost'] = 0
            numbers['sum'] = int(n[0]) + int(n[1]) + int(n[2])
            numbers['buy'] = False
            numbers['buy sum'] = False
            
            if n not in covered_for:
                distinct_numbers.append(n)
                if unique_digits(n):
                    distinct_numbers_unique_digits.append(n)
                    numbers['buy'] = True
                    numbers['cost'] += 1
                    total_cost += 1

                    if numbers['sum'] not in sums:
                        sums.append(numbers['sum'])
                        numbers['buy sum'] = True
                        numbers['cost'] += 1
                        total_cost += 1

                for p in permutate(n):
                    if p not in covered_for:
                        covered_for.append(p)
            log_file.writerow(numbers)
    
    print("$%d spent" % total_cost)
    print("%d distinct numbers" % len(distinct_numbers))
    #print("chances of getting a distinct number: %.2f" %(len(distinct_numbers)/1000.0))
    #print(distinct_numbers)
    print("%d distinct numbers with unique digits" % len(distinct_numbers_unique_digits))
    #print("chances of getting a distinct number with unique digits: %.2f" %(len(distinct_numbers_unique_digits)/1000.0))
    #print(distinct_numbers_unique_digits)

# To do: 
# * get stats on existing numbers
