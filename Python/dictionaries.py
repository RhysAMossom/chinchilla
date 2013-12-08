ages = {'Mom':44, 'Dad':42}
print "ages =", ages
print "ages['Dad'] is ",ages['Dad']

ages['Sister'] = 18
ages['Dad'] = 43

print "new ages['Dad'] is", ages['Dad'],'\n'

for x in ages:
	print 'The key "%s" in "ages" has a value = %d' %(x, ages[x])


print "\n'43' in 'ages' is ",(43 in ages),"because '43' is not a key in 'ages'\n"
#>>False #Because 43 is not a key, it is a value


print "ages.keys() is", ages.keys()
#>>['Dad', 'Sister', 'Mom']


print "ages.values() is", ages.values()
#>>[42, 18, 44]


print "ages.items() is", ages.items()
#>>[('Dad', 42), ('Sister', 18), ('Mom', 44)]

print "\nThe lenght of 'ages' is", len(ages)
#>>3

