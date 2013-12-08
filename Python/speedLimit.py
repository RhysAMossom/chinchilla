def speedLimit():
    # WE ASSUME SPEED LIMIT IS LESS THAN 90 MILES PER HOUR
    speed = int(raw_input("Enter speed of the car  "))
    limit = int(raw_input("Enter speed limit of the road  "))
    if speed > 90:
        fine = 200 + 5*(speed - limit)
    elif speed > limit:
        fine = 50 + 5*(speed - limit)
    elif speed <= limit - 20:
        fine = 90
    else:
        fine = 0
        print "No Fine"
    print    
    print "Fine value is $ ", fine
    print "Keep Driving Safely!"

speedLimit()
