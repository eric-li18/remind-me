from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.common.exceptions import NoSuchElementException
from getpass import getpass
import time
import os

class formFillOut():
    def __init__(self, login,password):
        self.browser = webdriver.Chrome("chromedriver.exe")
        self.login = login
        self.password = password
        
    def getURL(self, url,userID, passID):
        self.browser.get(url)
        loginInput = self.browser.find_element_by_id(userID)
        loginInput.send_keys(self.login)
        loginInput.send_keys(Keys.ENTER)
        passwordInput = self.browser.find_element_by_id(passID)
        passwordInput.send_keys(self.password)
        passwordInput.send_keys(Keys.ENTER)
    
    def submitHW(self,file):
        time.sleep(0.75)
        self.browser.find_element_by_partial_link_text("Graded HW").click()
        try:
            self.browser.find_element_by_link_text("Re-submit Assignment").click()
            self.browser.find_element_by_class_name("input-file").send_keys(os.getcwd()+file)
        except NoSuchElementException:
            try:
                self.browser.find_element_by_class_name("icon-check")
                print("\n ****The assignment was already submitted!****")
            except NoSuchElementException:
                print("\n ****Are you on the right webpage?****")


    def checkMarkus(self):
        time.sleep(0.75)
        markList = self.browser.find_elements_by_tag_name("tr")
        for i in markList:
            #allEntries = i.find_elements_by_tag_name("tr")
            #for j in i: 
            name = i.find_elements_by_css_selector("td > a")[0]
            print(name.text)
            try:
                assignment = i.find_elements_by_css_selector("td > a")[1]
                print(assignment.text)
            none = i.find_elements_by_css_selector("td")[2]
            print(none.text)

            




    def __exit__(self,exc_type, exc_value, traceback):
        self.browser.close()

user = getpass("Username:")
pwd = getpass()
x = formFillOut(user,pwd)
#x.getURL("https://q.utoronto.ca/courses/96305/assignments","username","password")
#x.submitHW("/Graded HW10.pdf")
x.getURL("https://markus.utsc.utoronto.ca/cscb09s19/en/assignments","user_login","user_password")
x.checkMarkus()
