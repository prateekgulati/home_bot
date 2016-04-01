import serial
import time

ard = serial.Serial('COM5',9600,timeout=5)
time.sleep(2) # wait for Arduino

# Symultaneous read and write section
def getData(command):
    ard.flush()
    setTemp1 = str(command)
    print ("Python value sent: ")
    print (setTemp1)
    ard.write(setTemp1)
    time.sleep(1)
    # Serial read section
    msg = ard.read(ard.inWaiting()) # read all characters in buffer
    print ("Message from arduino: ")
    print msg
    return msg



