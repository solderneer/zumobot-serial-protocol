#!/usr/bin/env python

# This module provides methods to access the zumobot interface

import serial
ser = serial.Serial()

def init(baudrate, port):
    global ser
    ser.baudrate = baudrate
    ser.port = port

    ser.open()

    if ser.is_open:
        return True
    else:
        return False

# Takes a value between 0 and 200 and maps it to each of the motors
def setMotors(rmotor, lmotor, rdir, ldir):
    startByte = 128
    global ser

    if(rdir == True) and (ldir == True):
        startByte = startByte + 3
    elif rdir == True:
        startByte = startByte + 1
    elif ldir == True:
        startByte = startByte + 2
    else:
        pass

    if (-200<lmotor<200) and (-200<rmotor<200):
        ser.write(startByte)
        ser.write(lmotor)
        ser.write(rmotor)
        return True
    else:
        return False



