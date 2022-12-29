from RPLCD.gpio import CharLCD
from RPi import GPIO
import os
import time

interfaces = {
    'wlan0': '',
    'eth0': ''
}

def get_ip(interface_name):
    ip_addr = os.popen('ifconfig | grep -A 1 ' + interface_name  + ' | tail -n 1 | grep inet | awk \'{print $2}\'').read()

    if len(ip_addr) == 0:
        return '-.-.-.-'
    else:
        return ip_addr

try:
    GPIO.setwarnings(False)

    lcd = CharLCD(pin_rs=7, pin_rw=13, pin_e=11, pins_data=[37, 35, 33, 31], numbering_mode=GPIO.BOARD, cols=16, rows=2, auto_linebreaks=True)

    while True:
        for i in interfaces.keys():
            interfaces[i] = get_ip(i)

            lcd.write_string(i+':')
            lcd.crlf()
            lcd.write_string(interfaces[i])
            time.sleep(3)
            lcd.clear()
except:
    print('Something went wrong...')
finally:
    lcd.close(clear=True)
