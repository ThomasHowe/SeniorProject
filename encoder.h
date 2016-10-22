/*!
 * @file ece486_biquad.h
 *
 * @brief ECE 406 Fall 2016 Senior Project "include" file
 *
 * @author Alan Kwok
 * @author Christopher Verbitzki
 * 
 * @date October 22, 2016
 */

#ifndef ENCODER.H
#define ENCODER.H

struct let{
	int size;
	int letval;
};

void timerinitialize(void);
void timer(void);
void transmitstring(char **message, int *sizes);
void dot(void);
void dash(void);
void Toggle_gpio(void);
void delayms(int time);
struct let chooseemit(char a, struct let letter);

#endif
