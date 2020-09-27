# NanoClock1414
An HPDL1414 clock display powered by Arduino Nano and 74HC595

## Introduction

<p align="center"><img src="https://github.com/senglk/NanoClock1414/blob/master/images/clock1414.jpg" alt="Picture of finished NanoClock1414" width="401" height="316" /></p>

This set up is meant to be plugged into a computer via USB cable, and displays the time on the computer in a 24-hour clock format on the HPDL1414 via the Arduino Nano and 74HC595.

Due to the lack of a RTC module, the hardware set up presented here will not be able to preserve time information once the USB cable is unplugged. Hence, it will always need to be connected to a computer to set the initial time upon power up. Since the USB cable cannot be removed after power up, the methodology of updating time is developed around this USB cable.

The Arduino code was based off the code from [HPDL-1414 16x2 LED Display](https://hackaday.io/project/168425-hpdl-1414-16x2-led-display) and would be a good exercise for those hoping to learn more about Shift Registers (74HC595 in this case).

## Prerequisites

### Arduino IDE

As the `NanoClock1414.ino` file would be uploaded to the Arduino Nano, means to upload the code to the Arduino needs to be established. The [Arduino IDE](https://www.arduino.cc/en/Guide) can be used to upload the code to the Arduino Nano. The following instructions proceeds under the assumption that the Desktop IDE is installed.

### Python 3

The accompanying `clock1414.py` script was written for Python 3. The script requires the following library:

### pySerial

[pySerial ](https://pyserial.readthedocs.io/en/latest/pyserial.html) provides the interface to the serial communication backend. The pySerial library can be installed using [pip](https://pypi.org/project/pip/) using the following command:

    pip install pyserial

For more information, one may refer to the [pySerial installation instructions](https://pyserial.readthedocs.io/en/latest/pyserial.html#installation).

## Usage

1. Wire up the Arduino Nano, 74HC595 Shift Register, and HPDL1414 as per the schematic shown above.

2. Connect your computer to the the Arduino Nano using a USB cable.

3. Download and Save the `NanoClock1414.ino` file from this repository to a directory of your choice. Note that the filename and the folder name would need to be the same.

4. Open the downloaded `Nanoclock1414.ino` file on the Arduino IDE, select the appropriate port (e.g. `COM6` on Windows, or `/dev/ttyUSB0` on Linux), and click on upload to initiate the upload process Arduino Nano. After successfully compiling the code and uploading to the Arduino Nano, you can test of the set up is ready for the next step by opening the serial monitor, setting baudrate to 19200, and typing in 4 numbers followed by pressing enter. The number should now be displayed on the HPDL1414. The HPDL1414 is able to display capital letters and most symbols on the keyboard. Refer to the HPDL1414 datasheet for a list of letters and symbols that can be displayed on the HPDL1414!

5. Download and Save either `clock1414.py` or `clock1414_v2.py` file from this repository to a directory of your choice. Essentially, `clock1414.py` checks if the 24-hour time has changed every second, and sends the new time over to the Arduino Nano if it has, while the `clock1414_v2.py` checks the time and sleeps till the next minute, where (when?) it will update the time and adjust the sleep time to the next minute. `clock1414.py` is easier to read and understand, while `clock1414_v2.py` borrows threading concepts.

6. Update the port number in the `clock1414.py` to reflect the port which the Arduino Nano is connected to. For example, on Windows this may be `COM6`, while on Linux this may be `/dev/ttyUSB0` instead.

7. Execute the script:

Linux:

    $python3 clock1414.py

Windows:

    >py -3 clock1414.py

8. The Python script is terminated via keyboard interrupt by pressing `Ctrl+C'.

## Differences Between Linux and Windows Python Scripts
The Windows version and Linux versions of the Python scripts presented here differs in the default port, and the removal of `'HUP'` from the list in the for loop in `"__main__"` for the Windows version. i.e. change the line

    for sig in ('TERM', 'HUP', 'INT'):

to

    for sig in ('TERM', 'INT'):

This is because on Windows, [there is no SIGHUP](https://stackoverflow.com/a/48336681/5317990), and the interpreter will be throwing an AttributeError.
