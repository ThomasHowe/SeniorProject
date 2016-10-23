#include <stdio.h>
#include <stdlib.h>
#include "stm32l0xx.h"                  // Device header
#include "stm32l053xx.h"

#define ONEHUNDREDMS 0x33333						//Delayms value for delaying onehundred ms
#define SEVENHMS 818500									//To use as Delay between Words

struct let{
	int size;
	int letval;
};

void initialize_USART(void);
void timerinitialize(void);
void timer(void);
void transmitstring(char **message, int *sizes);
void dot(void);
void dash(void);
void Toggle_gpio(void);
void delayms(int time);
void SleepUsart(void);
struct let chooseemit(char a, struct let letter);

int main(void) {
	int i=1;
	char **message;
	int size[5];
	
	message = (char **)malloc(5 * sizeof(char *));
	for(i=0;i<5;i++){
		message[i] = (char *)malloc(10 * sizeof(char *));
	}
	
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
	size[4] = 3;
	//SystemCoreClockConfigure();
	//timerinitialize();
	RCC->IOPENR  |=  ((1UL << 0));
	GPIOA->MODER   &= ~((3UL << 2*4));
  GPIOA->MODER   |=  ((1UL << 2*4));
  GPIOA->OTYPER  &= ~((1UL <<   4));
  GPIOA->OSPEEDR &= ~((3UL << 2*4));
  GPIOA->OSPEEDR |=  ((1UL << 2*4));
  GPIOA->PUPDR   &= ~((3UL << 2*4));
	//GPIOA->ODR |= ((1UL << 4));
	//while(1);
	/*for(i=0;i<10000;i++){
	}
	GPIOA->ODR &= ~((1UL << 4));
	//while(1){
		GPIOA->ODR |= ((1UL << 4));
		timerinitialize();
		timer();
		GPIOA->ODR &= ~((1UL << 4));
		timer();
	//}
	while(1);*/
	/*for(i=0;i<5;i++){
		free(message[i]);
	}
	free(message);*/
		//i++;
		//delayms(0xFFFFE);
		//GPIOA->ODR |= ((1UL << 4));
		//__nop();
		
		//while(1);
		//__nop();
		//GPIOA->ODR &= ((1UL << 4));
		//while(1);
	
	transmitstring(message, size);
	for(i=0;i<5;i++){
		free(message[i]);
	}
	free(message);
	/*while(1){
		GPIOA->ODR |= ((1UL << 4));
		delayms(5 * ONEHUNDREDMS);
		delayms(5 * ONEHUNDREDMS);
	}*/
	while(1);
}


void timerinitialize(void){
	/*NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_SetPriority(TIM2_IRQn, 1);
	RCC->APB1ENR &= ~(0x80000000);
	RCC->APB1ENR |= 0x80000000;
	RCC->APB1SMENR |= 0x80000000;
	RCC->CCIPR &= ~(0xC0000);
	RCC->CCIPR |=  (0xC0000);
	//LPTIM1->CFGR |= 0xC00;
	//LPTIM1->CFGR |= 
	LPTIM1->IER |= 0x2;
	LPTIM1->ARR &= ~(0xFFFF);
	LPTIM1->ARR |= 0x00FF;
	LPTIM1->CMP |= 0xFFFF;
	LPTIM1->CR |= 0x1;
	LPTIM1->CR|=0x2;*/
	/*RCC->APB1ENR |= 0x1;
	RCC->APB1SMENR |= 0x1;
	//TIM2->CR1 |= 0x8;
	//TIM2->CR1 |= 0x10;
	TIM2->PSC |= 0xFFFF;
	NVIC_EnableIRQ(SysTick_IRQn);
	NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
	TIM2->DIER |= 0x0002;
	TIM2->ARR = 0xCFF0;
	TIM2->CCR1 |= 0x100;
	TIM2->EGR |= TIM_EGR_CC1G;*/
	//TIM2->CR1 |= TIM_CR1_CEN;
	SysTick->CTRL = 0;
	SysTick->LOAD = 0xFFFFE;
	NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
	SysTick->VAL = 0;
	SysTick->CTRL |= 0x4;
	SysTick->CTRL |= 0x1;
	SysTick->CTRL |= 0x2;
}	

void timer(void){
	//int i;
	//TIM2->CR1 |= TIM_CR1_CEN;
	//for(i=0;i<10000;i++);
	//LPTIM1->CR |= 0x1;
	//LPTIM1->CR|=0x2;
	//TIM2->SR &= ~(0x1E5F);
	//TIM2->SR &= ~(0x1E5F);
	GPIOA->ODR |= ((1UL << 4));
	while(1){
		delayms(1048574);

	}
	//__wfi();
	//TIM2->SR &= ~(0x0001);
}
void SysTick_Handler(void){
	//GPIOA->ODR |= ((1UL << 4));
	Toggle_gpio();
	
	SysTick->CTRL = 0;
	/*int i = 0;
	i++;*/
}

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
			//printf(“Only lower case letters no spaces”);
			exit(2);			//error checking
	}
}
}

void initialize_USART(void){
	GPIOA->MODER &= ~((0x00200000));
	GPIOA->MODER |=  ((0x00200000));
	GPIOA->AFR[1] &= ~((0x00000F00));
	USART1->BRR = 160000 / 96; /* (1) */
	USART1->CR1 = USART_CR1_RXNEIE | USART_CR1_RE | USART_CR1_UE;
}

char Receive_Byte(void){
	char x;
	if((USART1->ISR & USART_ISR_RXNE) == USART_ISR_RXNE){
		x = (uint8_t)(USART1->RDR); /* Receive data, clear flag */
	}
	return x;
}

void SleepUsart(void){					//Page 19 on Command Sheet for more info
	
}


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
	SysTick->CTRL = 0;
	SysTick->LOAD = time;
	NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
	SysTick->VAL = 0;
	SysTick->CTRL |= 0x4;
	SysTick->CTRL |= 0x1;
	SysTick->CTRL |= 0x2;
	__wfi();
}

void Toggle_gpio(void){
	/*if((GPIOA->ODR & GPIO_ODR_OD4) == GPIO_ODR_OD4){
		GPIOA->ODR &= ~((1UL << 4));
	}
	else GPIOA->ODR |= ((1UL << 4));*/
	GPIOA->ODR &= ~((1UL << 4));
	;
}


