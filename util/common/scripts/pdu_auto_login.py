import time
import os
import argparse
from argparse import RawTextHelpFormatter
from selenium import webdriver
from selenium.webdriver.support.select import Select
from selenium.webdriver.chrome.options import Options

user_name = "apc"
pswd = "apc"

parser = argparse.ArgumentParser(description='Control PDU switching from cmd line.', formatter_class=RawTextHelpFormatter)
parser.add_argument('-u','--url', type=str, metavar='', required=True, help='PDU url')
parser.add_argument('-a','--action', type=int, metavar='', required=True, help="Action to perform. Pass below values w.r.t actions\
        \n1 - On Immediate\n2 - On Deleyed\n3 - Off Immediate\n4 - Off Delayed\n5 - Reboot Immediate\n6 - Reboot Delayed\n7 - Cancel pending commands")
parser.add_argument('-r','--relay', type=int, metavar='', required=True, help='Relay to which board is connected.')
args = parser.parse_args()

def select_outlet_action(driver, val):
    parse_outlet(driver)
    ctrl_outlet = Select(driver.find_element("name", "outlet_control_option"))
    if (val == 1):
        # On Immediate
        ctrl_outlet.select_by_value("01000000")
    elif (val == 2):
        # On Delayed
        ctrl_outlet.select_by_value("02000000")
    elif (val == 3):
        # Off Immediate
        ctrl_outlet.select_by_value("03000000")
    elif (val == 4):
        # Off Delayed
        ctrl_outlet.select_by_value("04000000")
    elif (val == 5):
        # Reboot Immediate
        ctrl_outlet.select_by_value("05000000")
    elif (val == 6):
        # Reboot Delayed
        ctrl_outlet.select_by_value("06000000")
    elif (val == 7):
        # Cancel pending commands.
        ctrl_outlet.select_by_value("07000000")
    else :
        print("Invalid outlet control action")

def select_outlet(driver, val):
    if (val == 1):
        driver.find_element("xpath", "//input[@value='?1']").click()
    elif (val == 2):
        driver.find_element("xpath", "//input[@value='?2']").click()
    elif (val == 3):
        driver.find_element("xpath", "//input[@value='?3']").click()
    elif (val == 4):
        driver.find_element("xpath", "//input[@value='?4']").click()
    elif (val == 5):
        driver.find_element("xpath", "//input[@value='?5']").click()
    elif (val == 6):
        driver.find_element("xpath", "//input[@value='?6']").click()
    elif (val == 7):
        driver.find_element("xpath", "//input[@value='?7']").click()
    elif (val == 8):
        driver.find_element("xpath", "//input[@value='?8']").click()
    else:
        print("Invalid outlet")

def init_chrome():
    print ("Initializing chrome....")
    options = webdriver.ChromeOptions()
    # Enable below line to hide chrome window.
    #options.headless = True
    options.add_argument('headless')
    options.add_argument('--no-sandbox')
    #options.add_argument('--user-data-dir=/tmp/profile')
    options.binary_location = '/usr/bin/google-chrome'
    service_log_path = "./chromedriver.log"
    service_args = ['--verbose']
    driver = webdriver.Chrome(options=options)
    driver.get(args.url)
    return driver


def login_pdu(driver):
    driver.find_element("name", "login_username").send_keys(user_name)
    driver.find_element("name", "login_password").send_keys(pswd)
    driver.find_element("name", "submit").click()
    time.sleep(3)

def parse_outlet(driver):
    driver.find_element("xpath", "//a[normalize-space()='Control']").click()
    driver.find_element("xpath", "//li[@class='dropdown open']//a[@class='dropdown-toggle'][normalize-space()='RPDU']").click()
    driver.find_element("xpath", "//a[@href='outlctrl.htm']").click()
    time.sleep(3)

def apply_changes(driver):
    driver.find_element("xpath", "//input[@name='submit']").click()
    driver.find_element("xpath", "//input[@value='Apply']").click()
    time.sleep(5)

if __name__ == "__main__":
    driver = init_chrome()
    login_pdu(driver)
    print ("Login sucessfull")
    select_outlet_action(driver,args.action)
    select_outlet(driver, args.relay)
    time.sleep(3)
    apply_changes(driver)
    print ("Relay %s has been sucessfully updated." % args.relay)
    driver.close()

# Follow below page to install require module for this script
# https://tecadmin.net/setup-selenium-with-python-on-ubuntu-debian/
