/*!
 * @file ece406 encoder_main.c
 *
 * @brief ECE 406 Fall 2016 Senior Project "include" file
 *
 * @author Alan Kwok
 * @author Thomas Howe
 * 
 * @date October 22, 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include "stm32l0xx.h"                  // Device header
#include "stm32l053xx.h"

#include "serial.h"
#include "encoder.h"

#define beep 0x33333

int main(void) {
  int i = 0;
  int count = 0;
  char longi = 0;
  char lat = 0;
  char alt = 0;
  initialize_pins();
  for(i=0;i<100;i++) {
    #beepandsleep;
  }
  if (!GPS_Status(longi,lat,alt,count)){
      //Toggle Transistor to cut power to GPS
      //Save Last measured Coord to be sent periodically  
  }
  packet = Receive_Coordinates();
  transmission = parse(packet);
  transmit_coord(transmission);
}
