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

//Length of a beep in Morse code for 100ms Beep and 900ms 
#define beep 0x33333

int main(void) {
	
	int i = 1; 
	static int status = 1;
	char **message;				//Storage of what will be sent via Morse code
	int size[5];
	volatile char buffer[128];
	char oldalt[10];//, *oldlong, *oldlat;
	
	struct gps newgps;
	//Allocate memory for message
	message = (char **)malloc(5 * sizeof(char *));
	for(i=0;i<5;i++){
		message[i] = (char *)malloc(30 * sizeof(char *));
	}
	
	//Callsigns to be sent via morse code 
	message[0][0] = 'K';			//Call sign of Alan Kwok
	message[0][1] = 'C';			
	message[0][2] = '1';
	message[0][3] = 'F';
	message[0][4] = 'K';
	message[0][5] = 'R';
	message[1][0] = 'K';			//Call Sign of Thomas Howe
	message[1][1] = 'C';
	message[1][2] = '1';
	message[1][3] = 'F';
	message[1][4] = 'K';
	message[1][5] = 'T';
	message[1][6] = '!';			//Used for Parsing
	size[0] = 6;
	size[1] = 7;
	size[2] = 0;
	size[3] = 6;
	size[4] = 0;
	/*------------------------------------------------------------------*/
	/*----------------------Initialize GPIO Pins------------------------*/
	RCC->IOPENR  |=  ((1UL << 0));							//Right now using GPIO4 as output
	GPIOA->MODER   &= ~((3UL << 2*4) | (3UL << 2*8));				
  	GPIOA->MODER   |=  ((1UL << 2*4) | (1UL << 2*8));				//Set GPIO4 as output mode
  	GPIOA->OTYPER  &= ~((1UL <<   4) | (1UL <<   8));				//sets output type
  	GPIOA->OSPEEDR &= ~((3UL << 2*4) | (3UL << 2*8));				//Sets speed
  	GPIOA->OSPEEDR |=  ((1UL << 2*4) | (1UL << 2*8));
  	GPIOA->PUPDR   &= ~((3UL << 2*4) | (3UL << 2*8));				//no pull up pull down
	GPIOA->ODR 			|= ((1UL <<   8));
	/*------------------------------------------------------------------*/
	
	initialize_USART();	//initialize the pins for USART communication
	
	//Infinite loop
	while(1){
		//Grabs GPS data
		newgps = Parser();
		//Grabs GPS data
		newgps = parserer(newgps.data);
		//Gets GPS data and gets it ready to send
		message[2] = newgps.data;
		size[2] = newgps.size[1];
		//CRC calculation and transmission
		message[3] = crc(message[2], size[2]);
		for(i=4;i>0;i--){
			message[3][i] = message[3][i-1];
		}
		message[3][0] = '!';		//Used for parsing
		message[3][5] = '+';		//Used for parsing
		//Demonstration for transmitting at 12, 7, and 17 words per minute
		blinkledtest();
		transmitstring(message,size);
		blinkledtest();
		transmitsevenwpm(message,size);
		blinkledtest();
		transmit17wpm(message,size);
	}
	
	//Free memory of message
	for(i=0;i<5;i++){
		free(message[i]);
	}
	free(message);
	
	//Infinite loop
	while(1);
}
