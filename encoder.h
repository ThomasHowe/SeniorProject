/*!
 * @file ece406 encoder.h
 *
 * @brief ECE 406 Fall 2016 Senior Project "include" file
 *
 * @author Alan Kwok
 * @author Thomas Howe
 * 
 * @date October 22, 2016
 */

#ifndef ENCODER.H
#define ENCODER.H

//Struct used to determine what character something is and how it should be transmitted in Morse
struct let{
	int size;
	int letval;
};

//Initilaize timer
void timerinitialize(void);
void timer(void);
//Transmit a string in Morse code
void transmitstring(char **message, int *sizes);
//A dot in Morse code
void dot(void);
//A dash in Morse code
void dash(void);
//Turn on and off
void Toggle_gpio(void);
//Control time delay to control length of dots and dashes for different speeds
void delayms(int time);
//Struct for choosing characters
struct let chooseemit(char a, struct let letter);

#endif
