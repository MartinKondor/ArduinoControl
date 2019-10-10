import sys

if str(sys.version).split('.')[0] != '2':
    print('\nThis example can only be used with Python 2.x.\n')
    exit(1)


import time

import serial  # Library needed to open serial connection
from serial.tools.list_ports import comports


PIN = 2
PORT = 'COM1'
DELAY_SECONDS = 0.25


# Determine the Arduino's port
for port in comports():
    if 'arduino' in port[1].lower():
        PORT = port[0]
        break

port = serial.Serial(port=PORT, baudrate=9600, timeout=0)  # Open the Serial port
print(port)


while True:
    port.write('S0|o{0}|h{0}|.'.format(PIN))  # Set PIN to OUTPUT and HIGH
    time.sleep(DELAY_SECONDS)
    
    port.write('S0|o{0}|l{0}|.'.format(PIN))  # Set PIN to OUTPUT and LOW
    time.sleep(DELAY_SECONDS)
