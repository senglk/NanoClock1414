#!/usr/bin/env python3

import serial
import datetime
import signal
from threading import Event

exitEvent = Event()

def main(ser):
    while not exitEvent.is_set():
        timeNow = datetime.datetime.now()
        nbytesSent = ser.write(timeNow.strftime('%H%M').encode('utf-8'))
        exitEvent.wait(60 - timeNow.second) # sleep till the next minute

def quit(signo, _frame):
    exitEvent.set()

if __name__ == "__main__":
    for sig in ('TERM', 'HUP', 'INT'):
        signal.signal(getattr(signal, 'SIG'+sig), quit)
    
    with serial.Serial('/dev/ttyUSB0', 19200, timeout=1) as ser:
        print('Sleeping for 2 seconds to let things stabalise...')
        exitEvent.wait(2)
        print('Starting clock...')
        main(ser)
    print('Exiting...')
