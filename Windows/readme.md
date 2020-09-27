The Python script to be executed from Windows to update the time periodically.

Chiefly, the `clock1414.py` checks if the 24-hour time has changed every second, and sends the new time over to the Arduino Nano if it has, while the `clock1414_v2.py` checks the time and sleeps till the next minute, where (when?) it will update the time and adjust the sleep time to the next minute.

The `clock1414.py` is easier to read and understand, while `clock1414_v2.py` borrows threading concepts.
