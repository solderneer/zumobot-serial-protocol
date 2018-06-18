#!/usr/bin/env python

import zumo
import time

def main():
    zumo.init(9600, '/dev/ttyMFD1')
    while True:
        zumo.setMotors(50,50,True,False)
        time.sleep(1)
        zumo.setMotors(50,50,False, True)

if __name__ == "__main__":
    main()
