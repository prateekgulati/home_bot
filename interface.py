__author__ = 'Prateek'

import serial
import time
import httplib
import urllib

ard = serial.Serial('COM5', 9600)
time.sleep(2)


# Symultaneous read and write from serialBoard
def getData(command, field):
    ard.flush()
    command = str(command)
    ard.write(command)
    time.sleep(1)
    msg = ard.read(ard.inWaiting())  
    print msg
    if msg is not None:
        params = urllib.urlencode({field: msg, 'key': 'Your API key'})
        conn = httplib.HTTPConnection("api.thingspeak.com:80")
    try:
        conn.request("POST", "/update", params)
        response = conn.getresponse()
        print msg
        print response.status, response.reason
        data = response.read()
        conn.close()
    except:
        print "connection failed"


while True:
    getData("Temperature", "field1")
    getData("Humidity", "field2")
    getData("LDR", "field3")
