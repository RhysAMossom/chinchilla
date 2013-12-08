def averageInterval():
    prompt = 'Enter a number. Type "done" when finished.   '
    numbers = []
    while True:
        numString = raw_input(prompt)
        if(numString == 'done'):
            break
        elif float(numString) in numbers:
            print 'Input already in list.'
            continue
        else:
            num = float(numString)
            if not numbers: # if len(numbers) == 0 SAME AS if numbers == []
                minimum = num
                maximum = num
            elif num > maximum:
                maximum = num
            elif num < minimum:
                minimum = num
            numbers.append(float(numString))
    if len(numbers) <= 1:
        print 'Not enough numbers.'
    else:
        answer = (maximum - minimum) / (len(numbers)-1)
        print 'The average interval is: ',answer
        print
    print numbers
averageInterval()
