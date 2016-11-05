#!/usr/bin/python
import sys
import pygame
import time
from RPi import GPIO
from array import array
from pygame.locals import *
from morse_lookup import *

#Modified from https://www.raspberrypi.org/learning/morse-code-virtual-radio/worksheet/

def wait_for_high(pin):
  while GPIO.input(pin):
    time.sleep(0.01)

def wait_for_low(pin):
  while not GPIO.input(pin):
    time.sleep(0.01)

def decoder():
  global down_time
  global buffer
  new_w = False
  while True:
    time.sleep(.01)
    down_duration = time.time() - down_time
    if len(buffer) > 0 and down_duration >= sys.argv:
      new_w = True
      big_string = "".join(buffer)
      try_decode(bit_string)
      del buffer[:]
    elif new_w and down_duration >= sys.argv*3:
      new_w = False
      sys.stdout.write(" ")
      sys.stdout.flush()

pin = 17
GPIO.setmode(GPIO.BOARD)
GPIO.setup(pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
  
DOT = "."
DASH = "-"

high_time = 0
high_duration = 0
down_time = 0
buffer = []

thread.start_new_thread(decoder, ())

while TRUE:
  wait_for_high(pin)
  high_time = time.time() #Record when the high signal is found
  wait_for_low(pin)
  down_time = time.time() #Record when the signal goes low
  high_duration = down_time - high_time #Length of time when signal goes high
  
  buffer.append(DASH if high_duration > sys.argv else DOT)

#wget http://goo.gl/aRjulj -) morse_lookup.py --no-check-certificate
#Above grabs Morse to Character code
