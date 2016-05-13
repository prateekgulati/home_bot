__author__ = 'Prateek'

import serial
import time

ard = serial.Serial('COM5',9600,timeout=5)
time.sleep(2) # wait for Arduino