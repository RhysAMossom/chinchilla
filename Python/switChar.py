def switChar(text):
    rev = ''
    for i in range(1,len(text)+1):
        rev += text[-i]
    return rev
    
# or use: for i in range(len(text)):
#           rev += text[len(text)-1-i]
