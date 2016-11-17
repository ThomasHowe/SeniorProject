#!/usr/bin/python
import pygame
import time
import serial
from RPi import GPIO
import thread
from array import array
from pygame.locals import *
from morse_lookup import *

pygame.mixer.pre_init(44100, -16, 1, 1024)
pygame.init()

ser = serial.Serial(
	port="/dev/ttyAMA0",
	baudrate = 9600,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE,
	bytesize=serial.EIGHTBITS,
	timeout=1
)


class ToneSound(pygame.mixer.Sound):
    def __init__(self, frequency, volume):
        self.frequency = frequency
        pygame.mixer.Sound.__init__(self, self.build_samples())
        self.set_volume(volume)

    def build_samples(self):
        period = int(round(pygame.mixer.get_init()[0] / self.frequency))
        samples = array("h", [0] * period)
        amplitude = 2 ** (abs(pygame.mixer.get_init()[1]) - 1) - 1
        for time in xrange(period):
            if time < period / 2:
                samples[time] = amplitude
            else:
                samples[time] = -amplitude
        return samples

def wait_for_keydown(pin):
    while GPIO.input(pin):
        time.sleep(0.01)
	#if time.time() - key_up_time > 3 and key_up_time > 0:
		#sys.exit()

def wait_for_keyup(pin):
    while not GPIO.input(pin):
        time.sleep(0.01)

def decoder_thread():
    global key_up_time
    global buffer
    global newbuffer
    i = 0
    new_word = False
    while True:
        time.sleep(.001)
	#if time.time() - key_up_time > 3 and key_up_time > 0:
		#sys.exit()
	if time.time() - key_up_time >= 0:
        	key_up_length = time.time() - key_up_time
        if len(buffer) > 0 and key_up_length >= .29 and state == 1:
            new_word = True
	    #print key_up_length
            bit_string = "".join(buffer)
            newbuffer.append(try_decode(bit_string))
	    if i > 0:
	   	if newbuffer[i-1] == 'E' and newbuffer[i] == 'E':
			del newbuffer[:]
			#print "whoaaa"
			i = -1
	    if i > 0:
	    	if newbuffer[i] == '+':
			str = ''.join(newbuffer)
			str2 = str.split("!")[1]
			print "%s" % str2
			ser.write(str2)
			ser.write("\r\n")
	    i=i+1
            del buffer[:]
        elif new_word and key_up_length >= .75:
            new_word = False
            sys.stdout.write(" ")
            sys.stdout.flush()

#tone_obj = ToneSound(frequency = 800, volume = .5)

pin = 7
GPIO.setmode(GPIO.BOARD)
GPIO.setup(pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

DOT = "."
DASH = "-"

state = 1
key_down_time = 0
key_down_length = 0
key_up_time = 0
buffer = []
newbuffer = []

thread.start_new_thread(decoder_thread, ())

print("Ready")

while True:
    wait_for_keydown(pin)
    key_down_time = time.time() #record the time when the key went down
    key_up_time = time.time()
    state = 0
    #tone_obj.play(-1) #the -1 means to loop the sound
    wait_for_keyup(pin)
    key_up_time = time.time() #record the time when the key was released
    #print key_up_time
    key_down_length = key_up_time - key_down_time #get the length of time it was held down for
    state = 1
    #tone_obj.stop()
    buffer.append(DASH if key_down_length > 0.19 else DOT)
    #print key_down_length
