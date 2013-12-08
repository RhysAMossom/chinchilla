from wordCount import *

def testingWordCount():
    fh = open('texto.txt', 'r')
    text = fh.read()
    fh.close
    text = text + ":;.,?0123456789!@#$%%^&*()~`-_=+{}\|'/><\\\""
    c = wordCount(text)

    #for i in c:
     #   print i *c[i] #This will print a lot of lines, be careful

    for word in c:
        if c[word] >= 5:
            print "%15s %10d" %(word,c[word])

testingWordCount()
