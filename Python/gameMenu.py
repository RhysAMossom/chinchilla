def gameMenu():
 print "Menu:"
   print
    print "1. New Game"
    print "2. Saved Game"
    print "3. Instructions"
    print "4. Exit"
    choice = raw_input("Please pick an option. ")
    print
    if choice == "1":
    print "You chose New Game"
    elif choice == "2":
    print "Loading Saved Game"
    elif choice == "3":
    print "The Instructions are..." 
    elif choice == "4":
    print "Thank you for playing. Good-Bye!"
    else:
    print "Wrong input. Program terminated."
