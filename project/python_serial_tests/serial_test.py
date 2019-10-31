#!/usr/bin/python
import serial
import time

# The following line is for serial over GPIO
bluetooth = '/dev/tty.HC-05-SerialPort'  # note I'm using Mac OS-X
usb = '/dev/cu.usbserial-1420'
arduino1 = serial.Serial()
arduino1.baudrate = 9600
arduino1.port = bluetooth
arduino1.timeout = 5

# ard = serial.Serial(port, 9600, timeout=5)
arduino1.open()
if(arduino1.is_open):
    time.sleep(2)  # wait for Arduino

    i = 0

    while (i < 4):
        # Serial write section

        setTempCar1 = 63
        setTempCar2 = 37
        arduino1.flush()
        setTemp1 = str(setTempCar1)
        setTemp2 = str(setTempCar2)
        print ("Python value sent: ")
        print (setTemp1)
        arduino1.write(setTemp1)
        # Shortened this to match the new value in your Arduino code
        time.sleep(1)

        # Serial read section
        # read all characters in buffer
        msg = arduino1.read(arduino1.inWaiting())
        print ("Message from arduino: ")
        print (msg)
        i = i + 1
    else:
        print "Exiting"
    arduino1.close()
    exit()
