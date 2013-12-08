def reverse(word):
    if len(word) <= 1:
        return word
    else:
        return word[-1] + reverse(word[:-1])
