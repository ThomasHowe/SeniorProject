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

#include <stdio.h>
#include <stdlib.h>
#include "stm32l0xx.h"                  // Device header
#include "stm32l053xx.h"

//Start timer
void timerinitialize(void){
	SysTick->CTRL = 0;
	SysTick->LOAD = 0xFFFFE;
	NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
	SysTick->VAL = 0;
	SysTick->CTRL |= 0x4;
	SysTick->CTRL |= 0x1;
	SysTick->CTRL |= 0x2;
}	

//Set timer
void timer(void){
	GPIOA->ODR |= ((1UL << 4));
	while(1){
		delayms(1048574);

	}
	//__wfi();
	//TIM2->SR &= ~(0x0001);
}

//Set SysTick control to zero
//Toggle the gpio
void SysTick_Handler(void){
	//GPIOA->ODR |= ((1UL << 4));
	Toggle_gpio();
	
	SysTick->CTRL = 0;
	/*int i = 0;
	i++;*/
}

//Function that establishes how to transmit in Morse
//A dot is a zero
//A dash is a one
//Bits are in reverse order
//LSB first, MSB last
struct let chooseemit(char a, struct let letter){
	switch (a) {
		case 'a': {
			letter.letval = 2;
			letter.size = 2;
			return letter;
		}
		case 'b': {
			letter.letval = 1;
			letter.size = 4;
			return letter;
		}
		case 'c': {
			letter.letval = 5;
			letter.size = 4;
			return letter;
		}
		case 'd': {
			letter.letval = 1;
			letter.size = 3;
			return letter;
		}
		case 'e': {
			letter.letval = 0;
			letter.size = 1;
			return letter;
		}
		case 'f': {
			letter.letval = 4;
			letter.size = 4;
			return letter;
		}
		case 'g': {
			letter.letval = 3;
			letter.size = 3;
			return letter;
		}
		case 'h': {
			letter.letval = 0;
			letter.size = 4;
			return letter;
		}
		case 'i': {
			letter.letval = 0;
			letter.size = 2;
			return letter;
		}
		case 'j': {
			letter.letval = 14;
			letter.size = 4;
			return letter;
		}
		case 'k': {
			letter.letval = 5;
			letter.size = 3;
			return letter;
		}
		case 'l': {
			letter.letval = 2;
			letter.size = 4;
			return letter;
		}
		case 'm': {
			letter.letval = 3;
			letter.size = 2;
			return letter;
		}
		case 'n': {
			letter.letval = 1;
			letter.size = 2;
			return letter;
		}
		case 'o': {
			letter.letval = 7;
			letter.size = 3;
			return letter;
		}
		case 'p': {
			letter.letval = 6;
			letter.size = 4;
			return letter;
		}
		case 'q': {
			letter.letval = 11;
			letter.size = 4;
			return letter;
		}
		case 'r': {
			letter.letval = 2;
			letter.size = 3;
			return letter;
		}
		case 's': {
			letter.letval = 0;
			letter.size = 3;
			return letter;
		}
		case 't': {
			letter.letval = 1;
			letter.size = 1;
			return letter;
		}
		case 'u': {
			letter.letval = 4;
			letter.size = 3;
			return letter;
		}
		case 'v': {
			letter.letval = 8;
			letter.size = 4;
			return letter;
		}
		case 'w': {
			letter.letval = 6;
			letter.size = 3;
			return letter;
		}
		case 'x': {
			letter.letval = 9;
			letter.size = 4;
			return letter;
		}
		case 'y': {
			letter.letval = 13;
			letter.size = 4;
			return letter;
		}
		case 'z': {
			letter.letval = 3;
			letter.size = 4;
			return letter;
		}
		case '1': {
			letter.letval = 30;
			letter.size = 5;
			return letter;
		}
		case '2': {
			letter.letval = 28;
			letter.size = 5;
			return letter;
		}
		case '3': {
			letter.letval = 24;
			letter.size = 5;
			return letter;
		}
		case '4': {
			letter.letval = 16;
			letter.size = 5;
			return letter;
		}
		case '5': {
			letter.letval = 0;
			letter.size = 5;
			return letter;
		}
		case '6': {
			letter.letval = 1;
			letter.size = 5;
			return letter;
		}
		case '7': {
			letter.letval = 3;
			letter.size = 5;
			return letter;
		}
		case '8': {
			letter.letval = 7;
			letter.size = 5;
			return letter;
		}
		case '9': {
			letter.letval = 15;
			letter.size = 5;
			return letter;
		}
		case '0': {
			letter.letval = 31;
			letter.size = 5;
			return letter;
		}
		case '.': {
			letter.letval = 42;
			letter.size = 6;
			return letter;
		}
		case '-': {
			letter.letval = 33;
			letter.size = 6;
			return letter;
		}
		default : {
			exit(2);			//error checking
		}
	}
}

//transmit a string in Morse code
void transmitstring(char **message, int *sizes){
	int i, k, j;
	struct let letter;
	for(i=0;i<5;i++){
		for(j=0;j<sizes[i];j++) {
				delayms(0xFFFFE);
				letter = chooseemit(message[i][j], letter);
				for(k=0;k<letter.size;k++) {
					if((letter.letval>>k)&1) dash();
					else dot();
				} 
		}
		delayms(0x16FFFE);
	}
}

//Sleep for the time set by delayms, 3x dot 
void dash(void) {
	GPIOA->ODR |= ((1UL << 4));
	delayms(0x16FFFE);
	
}

//Sleep for time set by delayms
void dot(void) {
	GPIOA->ODR |= ((1UL << 4));
	delayms(0xFFFFE);
}

//WFI used to enter sleep mode with low-power timer
void delayms(int time){
	SysTick->CTRL = 0;
	SysTick->LOAD = time;
	NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
	SysTick->VAL = 0;
	SysTick->CTRL |= 0x4;
	SysTick->CTRL |= 0x1;
	SysTick->CTRL |= 0x2;
	__wfi();
}

//Toggle ODR
void Toggle_gpio(void){
	GPIOA->ODR &= ~((1UL << 4));
	;
}
