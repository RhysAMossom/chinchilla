#import urllib
import string as s

PUNC = ":;.,?0123456789!@#$%%^&*()~`-_=+{}\|'/><\\\""

def wordCount(text):
    count = {}

##    for i in PUNC:
##        text = s.replace(text,i,'')
##    print text
##
##    text = text.lower()    
##    text = s.split(text," ")
##    print text

    wordList = text.split()
    for ind in range(len(wordList)):
        wordList[ind] = wordList[ind].lower()
        wordList[ind] = wordList[ind].strip(PUNC)
        
    for word in wordList:
        if word in count:
            count[word] += 1
        else:
            count[word] = 1
    return count
