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
        
    def signIn(self):
        self.browser.get("https://q.utoronto.ca/courses/96305/assignments")
        loginInput = self.browser.find_element_by_id("username")
        loginInput.send_keys(self.login)
        loginInput.send_keys(Keys.ENTER)
        passwordInput = self.browser.find_element_by_id("password")
        passwordInput.send_keys(self.password)
        passwordInput.send_keys(Keys.ENTER)
    
    def findHW(self):
        time.sleep(0.75)
        self.browser.find_element_by_partial_link_text("Graded HW").click()
        try:
            self.browser.find_element_by_link_text("Re-submit Assignment").click()
            self.browser.find_element_by_class_name("input-file").send_keys(os.getcwd()+"/Graded HW10.pdf")
        except NoSuchElementException:
            try:
                self.browser.find_element_by_class_name("icon-check")
                print("\n ****The assignment was already submitted!****")
            except NoSuchElementException:
                print("\n ****Are you on the right webpage?****")

    def __exit__(self,exc_type, exc_value, traceback):
        self.browser.close()

pwd = getpass()
x = formFillOut("lieric12",pwd)
x.signIn()
x.findHW()