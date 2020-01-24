import time

from serial import Serial  # Library needed to open serial connection


PIN_1 = 3
PIN_2 = 4
PORT = 'COM11'
DELAY_SECONDS = 0.05
PORT = Serial(port=PORT, baudrate=9600, timeout=0)  # Open the Serial port


def encode_command(command):
    return bytearray(command, encoding='utf-8')


print('-' * 50)
print('AC:', 'Connecting to:', PORT)
print('AC:', 'Press Ctrl+C to close the program.')

try:
    while True:
        PORT.write(encode_command('S0|o{0}|o{1}|h{0}|l{1}|.'.format(PIN_1, PIN_2)))
        time.sleep(DELAY_SECONDS)

        PORT.write(encode_command('S0|o{0}|o{1}|l{0}|h{1}|.'.format(PIN_1, PIN_2)))
        time.sleep(DELAY_SECONDS)

        PORT.write(encode_command('S0|o{0}|o{1}|l{0}|l{1}|.'.format(PIN_1, PIN_2)))
        time.sleep(DELAY_SECONDS)

except KeyboardInterrupt:
    pass
finally:
    PORT.close()
    print('AC:', 'Connection closed.')

print('-' * 50)
