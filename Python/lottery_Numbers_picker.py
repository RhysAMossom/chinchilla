#! /usr/bin/env python
from itertools import permutations

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
    
    for number in range(1000):
        n = "%.3d" % number
        if n in covered_for:
          continue
        else:
            distinct_numbers.append(n)
            if unique_digits(n):
                distinct_numbers_unique_digits.append(n)
            for p in permutate(n):
                covered_for.append(p)
    
    print("%d distinct numbers" % len(distinct_numbers))
    print("%d distinct numbers with unique digits" % len(distinct_numbers_unique_digits))
    print(distinct_numbers_unique_digits)


# To do: 
# * look at rules to see if this works
# * get stats on existing numbers
