#include <stdio.h>
#include <stdlib.h>
#include "stm32l0xx.h"                  // Device header
#include "stm32l053xx.h"
#include "string.h"

#define ONEHUNDREDMS 0x33333						//Delayms value for delaying onehundred ms
#define SEVENHMS 818500									//To use as Delay between Words

struct let{															//struct to hold morse code dots and dashes
	int size;
	int letval;
};

struct gps{
	char longi[10];
	char lati[10];
	char alti[10];
	char *data;
	char *preparsedata;
	int size[3];
};

void initialize_USART(void);												//Initializes USART pins to talk to GPS
char Receive_Byte(void);														//Receives one byte from RDR register in USART1				
struct gps parse(char *packet, int spot);
struct gps parserer(char *pong);
struct gps Parser(void);
void Transmit_Byte(char x);
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
	/*message[4][0] = '1';
	message[4][1] = '2';
	message[4][2] = '+';*/
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

	/*message[0][3] = Receive_Byte();
	message[0][4] = Receive_Byte();
	message[0][5] = Receive_Byte();*/
	//initialize_USART();
/*	message[0][1] = Receive_Byte();
	//initialize_USART();
	message[0][2] = Receive_Byte();
	//initialize_USART();
	message[0][3] = Receive_Byte();
	//initialize_USART();
	message[0][4] = Receive_Byte();*/
	//while(1){
	//	message[0][1] = Receive_Byte();
	/*message[0][1] = Receive_Byte();
	message[0][2] = Receive_Byte();
	message[0][3] = Receive_Byte();
	message[0][4] = Receive_Byte();
	message[0][5] = Receive_Byte();
	message[0][6] = Receive_Byte();
	message[0][7] = Receive_Byte();
		transmitstring(message, size);*/
		/*while(1){
		for(i=0;i<10;i++){
			Transmit_Byte(message[1][i]);
		}
		delayms(SEVENHMS);
	}*/
	//}
	for(i=0;i<5;i++){
		free(message[i]);
	}
	free(message);
	while(1);
}




void blinkledtest(void){
	int i;
	GPIOA->ODR |= ((1UL << 4));
	for(i=0;i<10;i++){
		GPIOA->ODR &= ~((1UL << 4));
		delayms(1 * ONEHUNDREDMS);
		delayms(7 * ONEHUNDREDMS);
	}
}
void SysTick_Handler(void){									//Goes here when Systick match interrupt occurs
	Toggle_gpio();														//Turns off GPIO pin
	SysTick->CTRL = 0;												//Turn off the systick timer so no more interrupts occur
}

struct let chooseemit(char a, struct let letter){		//Crazy switch case function to set up morse code
	switch (a) {
		case 'A': {
			letter.letval = 2;
			letter.size = 2;
			return letter;
		}
		case 'B': {
			letter.letval = 1;
			letter.size = 4;
			return letter;
		}
		case 'C': {
			letter.letval = 5;
			letter.size = 4;
			return letter;
		}
		case 'D': {
			letter.letval = 1;
			letter.size = 3;
			return letter;
		}
		case 'E': {
			letter.letval = 0;
			letter.size = 1;
			return letter;
		}
		case 'F': {
			letter.letval = 4;
			letter.size = 4;
			return letter;
		}
		case 'G': {
			letter.letval = 3;
			letter.size = 3;
			return letter;
		}
		case 'H': {
			letter.letval = 0;
			letter.size = 4;
			return letter;
		}
		case 'I': {
			letter.letval = 0;
			letter.size = 2;
			return letter;
		}
		case 'J': {
			letter.letval = 14;
			letter.size = 4;
			return letter;
		}
		case 'K': {
			letter.letval = 5;
			letter.size = 3;
			return letter;
		}
		case 'L': {
			letter.letval = 2;
			letter.size = 4;
			return letter;
		}
		case 'M': {
			letter.letval = 3;
			letter.size = 2;
			return letter;
		}
		case 'N': {
			letter.letval = 1;
			letter.size = 2;
			return letter;
		}
		case 'O': {
			letter.letval = 7;
			letter.size = 3;
			return letter;
		}
		case 'P': {
			letter.letval = 6;
			letter.size = 4;
			return letter;
		}
		case 'Q': {
			letter.letval = 11;
			letter.size = 4;
			return letter;
		}
		case 'R': {
			letter.letval = 2;
			letter.size = 3;
			return letter;
		}
		case 'S': {
			letter.letval = 0;
			letter.size = 3;
			return letter;
		}
		case 'T': {
			letter.letval = 1;
			letter.size = 1;
			return letter;
		}
		case 'U': {
			letter.letval = 4;
			letter.size = 3;
			return letter;
		}
		case 'V': {
			letter.letval = 8;
			letter.size = 4;
			return letter;
		}
		case 'W': {
			letter.letval = 6;
			letter.size = 3;
			return letter;
		}
		case 'X': {
			letter.letval = 9;
			letter.size = 4;
			return letter;
		}
		case 'Y': {
			letter.letval = 13;
			letter.size = 4;
			return letter;
		}
		case 'Z': {
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
		case '+': {
			letter.letval = 10;
			letter.size = 5;
			return letter;
		}
		case '$': {
			letter.letval = 33;
			letter.size = 6;
			return letter;
		}
		default : {
			//printf(“Only lower case letters no spaces”);
			//exit(2);			//error checking
			letter.size = 0;
			return letter;
	}
}
}

void initialize_USART(void){										//Set up pins for USART1
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE10)) | (GPIO_MODER_MODE10_1);	//SET to alt function mode
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE9)) | (GPIO_MODER_MODE9_1);
	GPIOA->AFR[1] = (GPIOA->AFR[1] & ~(0x00000FF0)) | (4 << (1 * 4)) | (4<<(2*4));	//Set to alt function for usart
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;																						//Turn on usart clock
	USART1->BRR = 160000 / 730; /* 9600 baud */
	USART1->CR1 = USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;																			//enable usart
}


void Transmit_Byte(char x){
	while((USART1->ISR & USART_ISR_TXE) == 0){
		;
	}
	USART1->TDR = x;
}

char Receive_Byte(void){
	char x;
//	int i;
	USART1->ICR |= ((1 << 3));
	//x = malloc(20 * sizeof(char));
	//for(i=0;i<20;i++){
	while((USART1->ISR & USART_ISR_RXNE) == 0){
		;
	}
	//if((USART1->ISR & USART_ISR_RXNE) == USART_ISR_RXNE){
		x = (uint8_t)(USART1->RDR); /* Receive data, clear flag */
	//}
//}
	return x;
}

/*void SleepUsart(void){					//Page 19 on Command Sheet for more info
	
}*/


void transmitstring(char **message, int *sizes){
	int i, k, j;
	struct let letter;
	for(i=0;i<5;i++){
		for(j=0;j<sizes[i];j++) {
				delayms(3 * ONEHUNDREDMS);
				letter = chooseemit(message[i][j], letter);
				for(k=0;k<letter.size;k++) {
					if((letter.letval>>k)&1) dash();
					else dot();
					delayms(1 * ONEHUNDREDMS);
				} 
		}
		delayms(5 * ONEHUNDREDMS);
	}
}
void dash(void) {
	GPIOA->ODR &= ~((1UL << 4));
	//GPIOA->ODR |= ((1UL << 4));
	delayms(3 * ONEHUNDREDMS);
	
}

void dot(void) {
	//GPIOA->ODR |= ((1UL << 4));
	GPIOA->ODR &= ~((1UL << 4));
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
	//GPIOA->ODR &= ~((1UL << 4));
	GPIOA->ODR |= ((1UL << 4));
	;
}
struct gps parse(char *packet, int spot){
   int i = 0;
   int n = 1;
	 struct gps bill;
	 int count=0;
   if(packet[spot] == 'G' && packet[spot+1] == 'P' && packet[spot+2] == 'G' && packet[spot+3] == 'G' && packet[spot+4] == 'A'){  //Checks to make sure its GPGGA msg
      for(i=spot; i<128;i++){                                                             //Traverses entire message
          if (packet[i] == ',') count++;                                                          //counts number of commas they are separators
          if(count == 2){                                                                       //if comma count is 2, get lattitude
             while(packet[i+n] != ','){                                                           //go until hits next comma
                bill.lati[n] = packet[i+n];
                n++;
                if(packet[i+n] == ',') bill.lati[n+1] = packet[i+n+1];                                    //Adds direction of coordinates
							  bill.size[0] = n+1;
             }
             i = i+n;                                                                           //Move to i+n in message and
	     count++;
	  }
	  if(count == 4){
	     while(packet[i+n] != ','){								//increment comma count
   		bill.longi[n] = packet[i+n];
		n++;
		if(packet[i+n] == ',') bill.longi[n+1] = packet[i + n + 1];
	     }
	     i = i+n;
	     count++;
	  }
	  if(count == 9){									//9 commas and we are at alt
		  while(packet[i+n] != ','){
			  bill.alti[n] = packet[i+n];
			  n++;
		  }
	  i = i+n;
	  count++;
   }
}
}
	 return bill;
}

struct gps Parser(void){
	char PING[5];
	char PONG[80] = "GPGGA";
	int i = 4;
	struct gps dmessage;
	
	while(PING[4] != 'A'){
		PING[0] = Receive_Byte();
		if(PING[0] == 'G'){
			PING[1] = Receive_Byte();
			if(PING[1] == 'P'){
				PING[2] = Receive_Byte();
				if(PING[2] == 'G'){
					PING[3] = Receive_Byte();
					if(PING[3] == 'G'){
						PING[4] = Receive_Byte();
					}
				}
			}
		}
	}
	while(PONG[i] != '*'){
		i++;
		PONG[i] = Receive_Byte();
	}
	dmessage.data = PONG;
	dmessage.size[0] = i;
	return dmessage;
}

/*struct gps parsing(char *ping){
	int i;
	struct gps result;
	for (i=0;i<128;i++){
		if (i < 110){
			if(ping[i] == 'G' && ping[i+1] == 'P' && ping[i+2] == 'G' && ping[i+3] == 'G' && ping[i+4] == 'A'){
				result;
			}
		}
	}
}*/

struct gps parserer(char *pong){
	//char pong[80] = "GPGGA,,,,,,0,,,,,,,,*63";
	struct gps result;
	char message[60];
	int las=0, laf=0, los=0, lof=0, als=0, alf=0;
	int i, j, size, ccount;
	ccount = 0;
	size = 70;

	for(i=0;i<size;i++){
		if(pong[i] == ','){
			ccount++;
			//printf("%d\n", ccount);
		}
		if(ccount == 2 && las == 0){
			las = i;
			//printf("%d\n", las);
		}
		if(ccount == 3 && laf == 0) laf = i;
		if(ccount == 4 && los == 0) los = i;
		if(ccount == 5 && lof == 0) lof = i;
		if(ccount == 9 && als == 0) als = i;
		if(ccount == 10 && alf == 0) alf = i;
	}
	//printf("hello there\n");
	/*if((laf-las) == 1){
			//printf("oh no\n");
	}*/
	for(i = las+1; i<laf; i++){
		message[j] = pong[i];
		if(i == (laf-1)){
			message[j+1] = pong[i+2];
			message[j+2] = pong[i+3];
			j++;
			j++;
		}
		j++;
	}
	for(i = los+1; i<lof; i++){
		message[j] = pong[i];
		if(i == (lof-1)){
			message[j+1] = pong[i+2];
			message[j+2] = pong[i+3];
			j++;
			j++;
		}
		j++;
	}
	for(i = als+1; i<alf; i++){
		message[j] = pong[i];
		if(i == (alf-1)){
			message[j+1] = pong[i+2];
			j++;
		}
		j++;
	}
	result.data = message;
	result.size[1] = j-1;
	/*for(i=0; i<j; i++){
		//printf("%c", message[i]);
	}*/
	return result;
}




