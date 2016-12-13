#!/usr/bin/python
import pygame
import time
import serial
from RPi import GPIO
import thread
from array import array
from pygame.locals import *
from morse_lookup import *
import subprocess

#Set up serial for connecting with HC-05 Bluetooth chip
ser = serial.Serial(
	port="/dev/ttyAMA0",
	baudrate = 9600,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE,
	bytesize=serial.EIGHTBITS,
	timeout=1
)

#Wait for key down
def wait_for_keydown(pin):
    while GPIO.input(pin):
        time.sleep(0.01)

#Wait for key up	
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
	if time.time() - key_up_time >= 0:
        	key_up_length = time.time() - key_up_time								#Length of time key is up
        if len(buffer) > 0 and key_up_length >= .29 and state == 1:							#Go through buffer only if down length is obtained
            new_word = True
            bit_string = "".join(buffer)
            newbuffer.append(try_decode(bit_string))
	    if i > 0:
	   	if newbuffer[i-1] == 'E' and newbuffer[i] == 'E':
			newbuffer = newbuffer[:1]									#From beginning to position one
			i = -1
	    if i > 0:
	    	if newbuffer[i] == '+' and newbuffer.count('!') == 2:
			str1 = ''.join(newbuffer)
			str2 = str1.split("!")[1]									#Split on ! and create new string
			print "%s" % str2
			str4 = str1.split("!")[2]									#Split on ! and create new string
			str4 = str4[:-1]										#Remove last character
			b = "+ "
			for char in b:
				str4 = str4.replace(char,"")								#Replace +
			p = subprocess.Popen(['./testtest',str2],stdout=subprocess.PIPE,stderr=subprocess.STDOUT)	#Call c program
			for line in iter(p.stdout.readline, b''):
				str3 = line.rstrip()									#Remove whitespace
			print("whoa its from python: " + str3)								#See what CRC is calculatated to be  
			print("\nhereis" + str4 + "here is"+str3)							#Compare string 3 and string 4 and print
			if str4 == str3:										#Compare above, if same, shows CRC worked
				print("whoa we made it")								#Shows that the CRC calculated by the encoder and decoder are the same
				ser.write(str2)
				ser.write("\r\n")
	    i=i+1
            del buffer[:]												#Clear buffer
        elif new_word and key_up_length >= .75:
            new_word = False												#Set new word to false
            sys.stdout.write(" ")
            sys.stdout.flush()												#Flush the buffer and write everything in buffer to terminal

#Set pin as pull up
pin = 7
GPIO.setmode(GPIO.BOARD)
GPIO.setup(pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

#Establish dots and dashes for Morse lookup table
DOT = "."
DASH = "-"

state = 1
key_down_time = 0
key_down_length = 0
key_up_time = 0
buffer = []		#For storing strings
newbuffer = []		#For storing strings

thread.start_new_thread(decoder_thread, ())

#Tells when the decoder is ready
print("Ready")

while True:
    wait_for_keydown(pin)
    key_down_time = time.time() 				#record the time when the key went down
    key_up_time = time.time()					#record the time when the key went up
    state = 0
    wait_for_keyup(pin)
    key_up_time = time.time() 					#record the time when the key was released
    key_down_length = key_up_time - key_down_time 		#get the length of time it was held down for
    state = 1							#Set to one when key down length is obtained
    buffer.append(DASH if key_down_length > 0.19 else DOT) 	#Dash if length greater than 190mS, otherwise, it is a DOT
