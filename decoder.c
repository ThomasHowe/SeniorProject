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

char storemessage(float clockcycle, char message);      //gets the data from the receiver
float averagespeed(char message);
float translatemessage(int message, int tobluetooth);     //Figures out what the coordinates are, then sends over bluetooth

int main(int argc, char **argv) {
  float speed = 0;
  speed = averagespeed(message);
  storemessage(speed,message);
  translatemessage(1,1);
  
}

char storemessage(float dot, char message) {
  //signal up time
  float sut = 0;
  //signal up length
  float sul = 0;
  //signal down time
  float sdt = 0;
  //signal down length
  float sdl = 0;
  sut = time;
  while(sul<3*dot) {
    sul = 0;
    sdl = 0;
    while(gpio != high);
    sdt = time();
    sul = sdt - sut;
    while(gpio != low);
    sdl = time() - sdt;
    sut = time();
    //dot is the length of a dot
    if (sdl == dot) {
      dash;
    }
    else {
      dot;
    }
}

//Uses the length of five dots to determine average speed.
//speed in wpm at which the Morse code is being transmitted.
//The speed of a dot length at 12 wpm is 100mS
float averagespeed(char dot) {
  float speed = 0;
  //signal up time
  float sut = 0;
  //signal up length
  float sul = 0;
  //signal down time
  float sdt = 0;
  //signal down length
  float sdl = 0;
  int i = 0;
  while(gpio != high) {
    sut = time();
    sul = time() - sut;
  }
  //.171 is roughly the time it takes for a dot at 7 wpm, 
  if (sul < .150 &&) {
    for(i = 1;i++;i<6) {
      while(gpio != high) {
        sut = time();
        sul = time() - sut;
      }
      while(gpio = low);
      speed += sul;
    }
    speed = speed / 5.0;
  }
}

float translatemessage(char message, int tobluetooth) {
  float speed = 0;
  speed = averagespeed(message);
  
  
}
