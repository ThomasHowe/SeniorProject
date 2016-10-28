#include <stdio.h>
#include <stdlib.h>
#include "stm32l0xx.h"                  // Device header
#include "stm32l053xx.h"

#define ONEHUNDREDMS 0x33333						//Delayms value for delaying onehundred ms
#define SEVENHMS 818500									//To use as Delay between Words

struct let{															//struct to hold morse code dots and dashes
	int size;
	int letval;
};

void initialize_USART(void);												//Initializes USART pins to talk to GPS
char Receive_Byte(void);														//Receives one byte from RDR register in USART1								
void blinkledtest(void);														//Test code for waking up processor from WFI
void transmitstring(char **message, int *sizes);		//Transmits GPS code, sends words with sizes of words stored in sizes array
void dot(void);																			//Transmits a Dot and turns off GPIO after
void dash(void);																		//Transmits a Dash and turns off GPIO after
void Toggle_gpio(void);															//Turns off the GPIO currently used to transmit
void delayms(int time);															//Delay function, will put microprocessor to sleep, one hundred ms has been defined
void SleepUsart(void);															//Currently not implemented, will put GPS to sleep mode to save power
struct let chooseemit(char a, struct let letter);		//Switch case function to determine morse code from letter

int main(void) {
	int i=1;
	char **message;
	int size[5];
	
	message = (char **)malloc(5 * sizeof(char *));
	for(i=0;i<5;i++){
		message[i] = (char *)malloc(10 * sizeof(char *));
	}
																										//Test Message to be sent via morse code 
	message[0][0] = 'h';
	message[0][1] = 'e';
	message[0][2] = 'l';
	message[0][3] = 'l';
	message[0][4] = 'o';
	message[1][0] = 'w';
	message[1][1] = 'o';
	message[1][2] = 'r';
	message[1][3] = 'l';
	message[1][4] = 'd';
	message[2][0] = 's';
	message[2][1] = 'o';
	message[2][2] = 's';
	message[3][0] = 's';
	message[3][1] = 'o';
	message[3][2] = 's';
	message[4][0] = 's';
	message[4][1] = 'o';
	message[4][2] = 's';
	size[0] = 5;
	size[1] = 5;
	size[2] = 3;
	size[3] = 3;
	size[4] = 4;
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
	blinkledtest();															//Blinks LED half a second on and off to test
	initialize_USART();													//initialize the pins for USART comm
	message[4][3] = Receive_Byte();							//Receive one byte from GPS for now
	transmitstring(message, size);
	for(i=0;i<5;i++){
		free(message[i]);
	}
	free(message);
	while(1);
}




void blinkledtest(void){
	
	GPIOA->ODR |= ((1UL << 4));
	while(1){
		GPIOA->ODR |= ((1UL << 4));
		delayms(5 * ONEHUNDREDMS);
		delayms(5 * ONEHUNDREDMS);
	}
}
void SysTick_Handler(void){									//Goes here when Systick match interrupt occurs
	Toggle_gpio();														//Turns off GPIO pin
	SysTick->CTRL = 0;												//Turn off the systick timer so no more interrupts occur
}

struct let chooseemit(char a, struct let letter){		//Crazy switch case function to set up morse code
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
		case ',': {
			letter.letval = 33;
			letter.size = 6;
			return letter;
		}
		case 'G': {
			letter.letval = 33;
			letter.size = 6;
			return letter;
		}
		default : {
			//printf(“Only lower case letters no spaces”);
			exit(2);			//error checking
	}
}
}

void initialize_USART(void){										//Set up pins for USART1
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE10)) | (GPIO_MODER_MODE10_1);
	GPIOA->AFR[1] = (GPIOA->AFR[1] & ~(0x00000FF0)) | (4 << (1 * 4)) | (4<<(2*4));
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	USART1->BRR = 160000 / 96; /* (1) */
	USART1->CR1 = USART_CR1_RE | USART_CR1_UE;
}

char Receive_Byte(void){
	char x;
	while((USART1->ISR & USART_ISR_RXNE) != USART_ISR_RXNE);
	if((USART1->ISR & USART_ISR_RXNE) == USART_ISR_RXNE){
		x = (uint8_t)(USART1->RDR); /* Receive data, clear flag */
	}
	return x;
}

/*void SleepUsart(void){					//Page 19 on Command Sheet for more info
	
}*/


void transmitstring(char **message, int *sizes){
	int i, k, j;
	struct let letter;
	for(i=0;i<5;i++){
		for(j=0;j<sizes[i];j++) {
				delayms(2 * ONEHUNDREDMS);
				letter = chooseemit(message[i][j], letter);
				for(k=0;k<letter.size;k++) {
					if((letter.letval>>k)&1) dash();
					else dot();
					delayms(1 * ONEHUNDREDMS);
				} 
		}
		delayms(4 * ONEHUNDREDMS);
	}
}
void dash(void) {
	GPIOA->ODR |= ((1UL << 4));
	delayms(3 * ONEHUNDREDMS);
	
}

void dot(void) {
	GPIOA->ODR |= ((1UL << 4));
	delayms(ONEHUNDREDMS);
}

void delayms(int time){
	SysTick->CTRL = 0;							//Clear systick control register to make sure it is off
	SysTick->LOAD = time;						//SET systick load to set time of systick timer
	NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);	//Turn on the interrupt
	SysTick->VAL = 0;								//clearerr timer
	SysTick->CTRL |= 0x4;						
	SysTick->CTRL |= 0x1;
	SysTick->CTRL |= 0x2;						//Turn on systick timer
	__wfi();												//Set processor into sleep mode and will wake up when interupt occurs.
}

void Toggle_gpio(void){
	GPIOA->ODR &= ~((1UL << 4));
	;
}

