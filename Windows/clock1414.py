import serial
import datetime
import time

timestr=''
lastSent=''
cont = True

with serial.Serial('COM6', 19200, timeout=1) as ser:
    # Sleep 1 second to let things stablise.
    # If weird symbols appear instead, or time is chopped up
    # Try increasing it to 2s
    time.sleep(1)
    try:
        while cont:
            time.sleep(1) # check time every 1 second
            timestr = datetime.datetime.now().strftime('%H%M')
            if lastSent == timestr:
                continue # if HHMM same as last update, go to next loop iteration
            bytesSent = ser.write(timestr.encode('utf-8'))
            lastSent = timestr
    except KeyboardInterrupt:
            cont = False
print('Exiting...')
