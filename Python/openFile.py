def openFile():
    while True:
        fName = raw_input("Enter name of input file:\n\n     ")
        try:
            fh = open(fName,'read')
        except IOError:
            print
            print "Could not open file %s." %fName
            # putting a 'continue' here is unnecessary
        else:
            break
    dot = fName.find('.')
    if dot != -1:
        outFile = fName[:dot]+'~'+fName[dot:]
    else:
        outFile =fName+'~'

    
    text = fh.read()
    fh.close()
    VOWELS = 'AEIOUaeiou'
    for vowel in VOWELS:
        text = text.replace(vowel,'')

    fh2 = open(outFile,'write')
    fh2.write(text)
    fh2.close()

    print "Output file is saved as %s" %outFile
    print
openFile()
