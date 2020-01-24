import time
from datetime import datetime

from serial import Serial  # Library needed to open serial connection


PIN = 'a5'
PORT = 'COM11'
PORT = Serial(port=PORT, baudrate=9600, timeout=0)  # Open the Serial port


def encode_command(command):
    return bytearray(command, encoding='utf-8')


print('-' * 50)
print('AC:', 'Connecting to:', PORT)
print('AC:', 'Press Ctrl+C to close the program.')

try:
    while True:
        PORT.write(encode_command('S0|i{0}|r{0}|.'.format(PIN)))  # Ask for analog status
        time.sleep(0.1)

        # Read untill ';' is found
        result = "|"

        while len(result) == 0 or result[-1] != ';':
            result += PORT.read().decode('utf-8')
            
            if result[-1] == '|':  # Clear string at each command start
                result = ""

        result = result[:-1]  # Skip the ';' character
        print('AC ({}):'.format(datetime.now()), '{} is at ->'.format(PIN.upper()), result)

except KeyboardInterrupt:
    pass
finally:
    PORT.close()
    print('AC:', 'Connection closed.')

print('-' * 50)
