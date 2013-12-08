import string as s
def cleanTextFile():
    fh = open('listPythonColorsUNCLEAN.txt','r')
    rawText = fh.read()
    fh.close()
    
    index = rawText.find('AliceBlue')
    rawText = rawText[index:]
    rawText = rawText.replace('  ','*')
    rawText = rawText.replace("\\",'*')
    rawText = rawText.replace("}",'')
    for i in range(10):
        rawText= rawText.replace(' '+str(i),'*')
    for x in range(5):
        for i in range(10):
            rawText = rawText.replace('*'+str(i),'*')
    rawText = rawText.replace("*",'')
    rawText = rawText.replace("\n",'*')
    rawText = s.join(rawText,'')
    rawText = s.split(rawText,"*")
    rawText = rawText[:-1]
    return rawText
cleanTextFile()

