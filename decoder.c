#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <serial.h>
#include <string.h>

float storemessage(int clockcycle, int message);      //gets the data from the receiver
float averagespeed(int message);
float translatemessage(int message, int tobluetooth);     //Figures out what the coordinates are, then sends over bluetooth

int main(int argc, char **argv) {
  storemessage(1,1);
  translatemessage(1,1);
  
}

float storemessage() {
  
  
}

//Uses the callsigns KC1FKR and KC1FKT seperated by a space to figure out the
//speed in wpm at which the Morse code is being transmitted.
//The speed of a dot length at 12 wpm is 100mS
float averagespeed(int message) {
  
  
}

float translatemessage(int message, int tobluetooth) {
  float speed = 0;
  speed = averagespeed(message);
  
  
}
