from xbee import XBee
import serial
import time

ser = serial.Serial('/dev/tty.usbserial-A702LD1P', 9600)

xbee = XBee(ser)

def beep():
	print "\a"

# Continuously read and print packets
while True:
    try:
        response = ser.readline()
        time.sleep(.2)
        if response=="1":
        	#print "WATCH OUT!! MOTHER IS APPROACHING!"
        	beep()
        else:
        	print "SO SAFE"

    except KeyboardInterrupt:
        break
        
ser.close()