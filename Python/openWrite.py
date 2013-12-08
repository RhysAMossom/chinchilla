def openWrite():
    fh = open("myFile.txt","write")
    for i in range(20):
        asterisks = '*'*i + '\n'
        fh.write(asterisks)
        fh.write("\n")
    fh.close
openWrite()
