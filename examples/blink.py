from time import sleep
from serial import Serial


port = Serial(port='COM1', baudrate=9600, timeout=0)

while True:
  if port.inWaiting() > 0:
    port.write('S0|o13|h13|.')
    sleep(.9)
    port.write('S0|l13|.')
