def main ():
    celsiuslist = range(0,101,10)
    for c in celsiuslist:
        fahrenheit = (9.0/5.0)*c + 32
        print "C =", c,"F =", fahrenheit
main()
