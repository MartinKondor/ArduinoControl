# ArduinoControl

[![version](https://img.shields.io/badge/version-v1.0.0-brightgreen.svg)](https://github.com/MartinKondor/ArduinoControl)
[![Project Status](https://img.shields.io/badge/status-active-brightgreen.svg)](https://github.com/MartinKondor/ArduinoControl/)
[![GitHub Issues](https://img.shields.io/github/issues/MartinKondor/ArduinoControl.svg)](https://github.com/MartinKondor/ArduinoControl/issues)
![Contributions welcome](https://img.shields.io/badge/contributions-welcome-blue.svg)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

A library for controlling arduino from the serial port, working with any programing language that can open serial connection.

## Getting Started

### Prerequisites

* Arduino
* Arduino IDE (optional)

## Deployment

Let's suppose that you want to control an Arduino from Python program.

First create an empty Arduino IDE project called `testac`:

```
void setup() {}
void loop() {}
```

After this, copy the content of the `source` library (which is in this repository) to the `testac` project's folder, and the directory will look like this:

```
testac/
    testac.ino
    arduino_control.ino
```

As a last step, go back to your `testac.ino` file and change it:

```
void setup() {
    Serial.begin(9600);
    ac_listen(9600);
}
void loop() {}
``` 

The Serial port must be opened for ArduinoControl and the same baudrate is needed. It is advised to do:

```
#define BAUD_RATE 9600

void setup() {
    Serial.begin(BAUD_RATE);
    ac_listen(BAUD_RATE);
}
void loop() {}
```

Now this project is ready to be uploaded to an Arduino and be used with the commands.

After the upload go to this project's directory and check the `examples/blink.py` for the python example.

## Commands

A message looks like:

```
[START][CONTENT][STOP]
```

Where in this library the start is an `S`:

```
S[CONTENT][STOP]
```

The stop is a `.`:

```
S[CONTENT].
```

The contents first part is the `AC_ID` (see the arduino_control file and change the ID for a number you want,
but the number must be > 0), this can be 0 but the 0 means that every arduino with any `AC_ID` will do as the `contents` say:

```
S[AC_ID][CONTENT].
```

The content is consisting of commands which are separated by a | and the commands can be upper or lower case but it is advised to use lowercase. 

So an abstract message looks like this:

```
S[AC_ID]| ... |[COMMAND]| ... |[COMMAND]| ... |.
```

Where the `...` are denoting more commands.

### Parts of a message

* S~ - Pass away, do nothing
* S - Start of message
* . - End of message
* in - Set the nth port to INPUT
* in - Set the nth port to INPUT_PULLUP
* on - Set the nth port to OUTPUT
* hn - Turns the nth output to HIGH
* ln - Turns the nth output to LOW
* If you whish to use an analog pin write an a before the command like: "ah1", will turn the 1st analog output to HIGH

### Examples

 * `"S0|o7|h7|."` - For all arduino (0), set 7 to OUPUT (o7), and turn it on (h7)
 * `"S2|ao1|ah1|."` - For the arduino numbered with (2), set Analog 1 to OUPUT (ao1), and turn it on (ah1)
 * `"S1|o1|h1|o2|l2|."` - For the arduino numbered with 1 (1), set 1 to OUPUT (o1), and turn it on (h1), then set 2 to OUTPUT (o2), and turn it off (l2)

## Tested boards

This software can be used with any programable arduino board, but we only tested these: 

* [Arduino Uno](https://store.arduino.cc/arduino-uno-rev3)
* [Arduino Mega 2560](https://store.arduino.cc/mega-2560-r3)


## Contributing

This project is open for any kind of contribution from anyone.

### Steps

1. Fork this repository
2. Create a new branch (optional)
3. Clone it
4. Make your changes
5. Upload them
6. Make a pull request here
7. Profit.

## Authors

* **[Martin Kondor](https://github.com/MartinKondor)**

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
