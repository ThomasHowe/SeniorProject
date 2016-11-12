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
	int i=1;
	char **message;
	int size[5];
	volatile char buffer[128];
	struct gps billy;
	message = (char **)malloc(5 * sizeof(char *));
	for(i=0;i<5;i++){
		message[i] = (char *)malloc(30 * sizeof(char *));
	}
																										//Test Message to be sent via morse code 
	message[0][0] = 'K';
	message[0][1] = 'C';
	message[0][2] = '1';
	message[0][3] = 'F';
	message[0][4] = 'K';
	message[0][5] = 'R';
	message[1][0] = ',';
	message[1][1] = '2';
	message[1][2] = '3';
	message[1][3] = '4';
	message[1][4] = 'E';
	message[1][5] = ',';
	message[1][6] = '2';
	message[1][7] = '3';
	message[1][8] = 'W';
	message[1][9] = ',';
	message[1][10] = '+';

	size[0] = 6;
	size[1] = 0;
	size[2] = 0;
	size[3] = 0;
	size[4] = 0;
	/*------------------------------------------------------------------*/
	/*----------------------Initialize GPIO Pins------------------------*/
	RCC->IOPENR  |=  ((1UL << 0));							//Right now using GPIO4 as output
	GPIOA->MODER   &= ~((3UL << 2*4));				
  GPIOA->MODER   |=  ((1UL << 2*4));					//Set GPIO4 as output mode
  GPIOA->OTYPER  &= ~((1UL <<   4));					//sets output type
  GPIOA->OSPEEDR &= ~((3UL << 2*4));					//Sets speed
  GPIOA->OSPEEDR |=  ((1UL << 2*4));
  GPIOA->PUPDR   &= ~((3UL << 2*4));					//no pull up pull down
	/*------------------------------------------------------------------*/
	//blinkledtest();															//Blinks LED half a second on and off to test
	initialize_USART();													//initialize the pins for USART comm
	billy = Parser();
	billy = parserer(billy.data);
	message[1] = billy.data;
	size[1] = billy.size[1];
	blinkledtest();
	transmitstring(message,size);

	for(i=0;i<5;i++){
		free(message[i]);
	}
	free(message);
	while(1);
}
