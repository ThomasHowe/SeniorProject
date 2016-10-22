/*!
 * @file ece406 serial.h
 *
 * @brief ECE 406 Fall 2016 Senior Project "include" file
 *
 * @author Alan Kwok
 * @author Thomas Howe
 * 
 * @date October 22, 2016
 */

#ifndef SERIAL.H
#define SERIAL.H

void initialize_pins(void); //Initialize Serial Pins to RX/TX modes

char *Receive_Coordinates(void); //Receives the string from GPS

int GPS_Status(char *longi, char *lat, char *alt, int count);

void transmit_coord(char *message);

void parse(void);

#endif
