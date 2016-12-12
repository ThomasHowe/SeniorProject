#include <stdio.h>
#include <stdlib.h>
#include "stm32l0xx.h"                  // Device header
#include "stm32l053xx.h"
#include "string.h"

#define SEVENWPM 0x578D4								//Dot length for 7wpm
#define TEENWPM 0x24242
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

// RF settings for CC1101



void initialize_USART(void);												//Initializes USART pins to talk to GPS
char Receive_Byte(void);														//Receives one byte from RDR register in USART1				
void transmitsevenwpm(char **message, int *sizes);
char crclookup(int value);
void transmit17wpm(char **message, int *sizes);
int GPScheck(char *oldalti, char *newalti, int status);
char * crc(char *input, int length);
struct gps parserer(char *pong);
struct gps Parser(void);
void Transmit_Byte(char x);
void blinkledtest(void);														//Test code for waking up processor from WFI
void transmitstring(char **message, int *sizes);		//Transmits GPS code, sends words with sizes of words stored in sizes array
void dot(void);																			//Transmits a Dot and turns off GPIO after
void dot7(void);
void dot17(void);
void dash(void);																		//Transmits a Dash and turns off GPIO after
void dash7(void);
void dash17(void);
void Toggle_gpio(void);															//Turns off the GPIO currently used to transmit
void delayms(int time);															//Delay function, will put microprocessor to sleep, one hundred ms has been defined
void SleepUsart(void);															//Currently not implemented, will put GPS to sleep mode to save power
struct let chooseemit(char a, struct let letter);		//Switch case function to determine morse code from letter

int main(void) {
	int i=1; 
	static int status=1;
	char **message;
	int size[5];
	volatile char buffer[128];
	char oldalt[10];//, *oldlong, *oldlat;
	
	struct gps newgps;
	message = (char **)malloc(5 * sizeof(char *));
	for(i=0;i<5;i++){
		message[i] = (char *)malloc(30 * sizeof(char *));
	}																									//Test Message to be sent via morse code 
	
	
	message[0][0] = 'K';
	message[0][1] = 'C';
	message[0][2] = '1';
	message[0][3] = 'F';
	message[0][4] = 'K';
	message[0][5] = 'R';
	message[1][0] = 'K';
	message[1][1] = 'C';
	message[1][2] = '1';
	message[1][3] = 'F';
	message[1][4] = 'K';
	message[1][5] = 'T';
	message[1][6] = '!';
	size[0] = 6;
	size[1] = 7;
	size[2] = 0;
	size[3] = 6;
	size[4] = 0;
	/*------------------------------------------------------------------*/
	/*----------------------Initialize GPIO Pins------------------------*/
	RCC->IOPENR  |=  ((1UL << 0));							//Right now using GPIO4 as output
	GPIOA->MODER   &= ~((3UL << 2*4) | (3UL << 2*8));				
  GPIOA->MODER   |=  ((1UL << 2*4) | (1UL << 2*8));					//Set GPIO4 as output mode
  GPIOA->OTYPER  &= ~((1UL <<   4) | (1UL <<   8));					//sets output type
  GPIOA->OSPEEDR &= ~((3UL << 2*4) | (3UL << 2*8));					//Sets speed
  GPIOA->OSPEEDR |=  ((1UL << 2*4) | (1UL << 2*8));
  GPIOA->PUPDR   &= ~((3UL << 2*4) | (3UL << 2*8));					//no pull up pull down
	GPIOA->ODR 			|= ((1UL <<   8));
	/*------------------------------------------------------------------*/
	//blinkledtest();															//Blinks LED half a second on and off to test
	initialize_USART();													//initialize the pins for USART comm
	while(1){
			newgps = Parser();
			newgps = parserer(newgps.data);
			message[2] = newgps.data;
			size[2] = newgps.size[1];
		  message[3] = crc(message[2], size[2]);
			for(i=4;i>0;i--){
				message[3][i] = message[3][i-1];
			}
			message[3][0] = '!';
			message[3][5] = '+';
		blinkledtest();
		transmitstring(message,size);
		blinkledtest();
		transmitsevenwpm(message,size);
		blinkledtest();
		transmit17wpm(message,size);
	}
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
		delayms(9 * ONEHUNDREDMS);
	}
}
void SysTick_Handler(void){									//Goes here when Systick match interrupt occurs
	Toggle_gpio();														//Turns off GPIO pin
	SysTick->CTRL = 0;												//Turn off the systick timer so no more interrupts occur
}


char * crc(char *input, int length)
{
	static char result[4];
	uint16_t crcvalue = 0xFFFF;
	int temp;
	int j;
	int i;
	int step;
	for(i=0;i<length;i++){ //For loop to traverse through each byte
		for(j=0;j<8;j++){ //For loop to apply each byte to the CRC
			step = ((input[i] >> j) & 1) ^ (crcvalue & 1);
			crcvalue = crcvalue >> 1;
			crcvalue = crcvalue & 0x7FFF;
			if(step){
				crcvalue = crcvalue ^ 0x8408;
			}
		}
	}
	crcvalue= ~crcvalue;
	for(i=0;i<4;i++){
		temp = (crcvalue >> (16 - (4+(4*i)))) & 0xF;
		result[i] = crclookup(temp);
	}
	return result;
}

char crclookup(int value){
	switch(value){
		case(0):
			return '0';
		case(1):
			return '1';
		case(2):
			return '2';
		case(3):
			return '3';
		case(4):
			return '4';
		case(5):
			return '5';
		case(6):
			return '6';
		case(7):
			return '7';
		case(8):
			return '8';
		case(9):
			return '9';
		case(10):
			return 'A';
		case(11):
			return 'B';
		case(12):
			return 'C';
		case(13):
			return 'D';
		case(14):
			return 'E';
		case(15):
			return 'F';
		default:
			return 'G';
	}
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
			letter.letval = 51;
			letter.size = 6;
			return letter;
		}			
		case '+': {
			letter.letval = 10;
			letter.size = 5;
			return letter;
		}
		case '!': {
			letter.letval = 53;
			letter.size = 6;
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
				delayms(2 * ONEHUNDREDMS + 0x4000);
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

void transmit17wpm(char **message, int *sizes){
	int i, k, j;
	struct let letter;
	for(i=0;i<5;i++){
		for(j=0;j<sizes[i];j++) {
				delayms(2 * ONEHUNDREDMS + 0x15000);
				letter = chooseemit(message[i][j], letter);
				for(k=0;k<letter.size;k++) {
					if((letter.letval>>k)&1) dash17();
					else dot17();
					delayms(1 * TEENWPM);
				} 
		}
		delayms(4 * ONEHUNDREDMS - 0x4000);
	}
}

void transmitsevenwpm(char **message, int *sizes){
	int i, k, j;
	struct let letter;
	for(i=0;i<5;i++){
		for(j=0;j<sizes[i];j++) {
				delayms(1 * ONEHUNDREDMS + 0x14000);
				letter = chooseemit(message[i][j], letter);
				for(k=0;k<letter.size;k++) {
					if((letter.letval>>k)&1) dash7();
					else dot7();
					delayms(1 * SEVENWPM - 0x300);
				} 
		}
		delayms(4 * ONEHUNDREDMS);
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
void dash7(void) {
	GPIOA->ODR &= ~((1UL << 4));
	//GPIOA->ODR |= ((1UL << 4));
	delayms(3 * SEVENWPM);
	
}

void dot7(void) {
	//GPIOA->ODR |= ((1UL << 4));
	GPIOA->ODR &= ~((1UL << 4));
	delayms(SEVENWPM - 0x300);
}
void dash17(void) {
	GPIOA->ODR &= ~((1UL << 4));
	//GPIOA->ODR |= ((1UL << 4));
	delayms(3 * TEENWPM);
	
}

void dot17(void) {
	//GPIOA->ODR |= ((1UL << 4));
	GPIOA->ODR &= ~((1UL << 4));
	delayms(TEENWPM);
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


struct gps Parser(void){
	char PING[5];
	static char PONG[100] = "GPGGA";
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
	//dmessage.data = "GPGGA,202410.000,4042.6000,N,07400.4858,W,1,4,3.14,276.7,M,-34.2,M,,*63";
	dmessage.size[0] = i;
	//dmessage.size[0] = 71;
	return dmessage;
}



struct gps parserer(char *pong){
	//char pong[80] = "GPGGA,,,,,,0,,,,,,,,*63";
	struct gps result;
	char message[60];
	int las=0, laf=0, los=0, lof=0, als=0, alf=0;
	int i, j=0, k, size, ccount;
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
	//message[j] = '!';
	//j++;
	k=0;
	for(i = las+1; i<laf; i++){
		message[j] = pong[i];
		result.lati[k] = pong[i];
		if(i == (laf-1)){
			message[j+1] = ',';
			message[j+2] = pong[i+2];
			message[j+3] = ',';
			j++;
			j++;
			j++;
		}
		j++;
	}
	k=0;
	for(i = los+1; i<lof; i++){
		message[j] = pong[i];
		result.longi[k] = pong[i];
		if(i == (lof-1)){
			message[j+1] = ',';
			message[j+2] = pong[i+2];
			message[j+3] = ',';
			j++;
			j++;
			j++;
		}
		j++;
		k++;
	}
	k=0;
	for(i = als+1; i<alf; i++){
		message[j] = pong[i];
		result.alti[k] = pong[i];
		if(i == (alf-1)){
			message[j+1] = pong[i+2];
			//message[j+2] = '+';
			//j++;
			j++;
		}
		j++;
		k++;
	}
	if(j < 5) return result;
	//message[j-1] = '!';
	result.data = message;
	result.size[1] = j-1;
	/*for(i=0; i<j; i++){
		//printf("%c", message[i]);
	}*/
	return result;
}

/*int GPScheck(char *oldalti, char *oldlat, char *oldlong, struct gps update, int status){
	double oldalt, newalt, oldlati, newlati, oldlongi, newlongi;
	if(status == 0) return 0;
	oldalt = atof(oldalti);
	newalt = atof(update.alti);
	oldlati = atof(oldlat);
	newlati = atof(update.lati);
	oldlongi = atof(oldlong);
	newlongi = atof(update.longi);
	if(newalt > 5000.0){
		return 2;
	}
	if(newalt < 5000.0 && status == 2){
		return 3;
	}
	if((status == 3) && ((newalt - oldalt) < 10) && ((newalt - oldalt) > -10) && ((newlati - oldlati) < 2) && ((newlati - oldlati) > -2) && ((newlongi - oldlongi) < 2) && ((newlongi - oldlongi) > -2)){
		return 0;
	}
	return status;
}*/
int GPScheck(char *oldalti, char *newalti, int status){
	int oldalt, newalt;
	if(status == 0) return 0;
	oldalt = sscanf(oldalti,"%d",&oldalt);
	newalt = sscanf(newalti,"%d",&newalt);
	if(newalt > 5000){
		return 2;
	}
	if(newalt < 5000 && status == 2){
		return 3;
	}
	if((status == 3) && ((newalt - oldalt) < 20) && ((newalt - oldalt) > -20)){
		return 0;
	}
	return status;
}

/*MCSM0(0x18) = 00000110;	*/
/*void spigpio(void){
	RCC->IOPENR |= ((0x2));
	GPIOA->MODER &= ~GPIO_MODER_MODE15;
	GPIOA->MODER |= GPIO_MODER_MODE15_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE12;
	GPIOA->MODER |= GPIO_MODER_MODE12_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE11;
	GPIOA->MODER |= GPIO_MODER_MODE11_1;
	GPIOB->MODER &= ~GPIO_MODER_MODE3;
	GPIOB->MODER |= GPIO_MODER_MODE3_1;
	GPIOA->AFR[1] &= ~(GPIO_AFRH_AFRH7 | GPIO_AFRH_AFRH4 | GPIO_AFRH_AFRH3);
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL3);
}*/

//void initializeSPI(void){
	/*	Pins Required for SPI: SCLK = PB_3, NSS = PA_15, MOSI = PA_12, MISO = PA_11	*/
//	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
//	SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR; /* (1) */
//	SPI1->CR2 = SPI_CR2_SSOE | SPI_CR2_RXNEIE; /* (2) */
//	SPI1->CR1 |= SPI_CR1_SPE;
//}


