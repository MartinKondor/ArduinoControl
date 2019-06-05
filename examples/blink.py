import time
import serial  # library needed to open serial connection


# open the COM1 port with the baudrate 9600
port = serial.Serial(port='COM1', baudrate=9600, timeout=0)


# loop 10 times
iter = 0
while True:
  if port.inWaiting() > 0:
    port.write('S0|o13|h13|.')
    time.sleep(.9)
    port.write('S0|l13|.')

    iter += 1
    if iter >= 10:
        break
    