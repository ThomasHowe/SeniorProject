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

//Test code for waking up processor from WFI
void blinkledtest(void){
	int i;
	GPIOA->ODR |= ((1UL << 4));
	for(i=0;i<10;i++){
		GPIOA->ODR &= ~((1UL << 4));
		delayms(1 * ONEHUNDREDMS);
		delayms(9 * ONEHUNDREDMS);
	}
}

//SysTick for STM
void SysTick_Handler(void){		//Goes here when Systick match interrupt occurs
	Toggle_gpio();			//Turns off GPIO pin
	SysTick->CTRL = 0;		//Turn off the systick timer so no more interrupts occur
}

//Calculate CRC value
char * crc(char *input, int length)
{
	static char result[4];
	uint16_t crcvalue = 0xFFFF;
	int temp;
	int j;
	int i;
	int step;
	for(i=0;i<length;i++){ 				//For loop to traverse through each byte
		for(j=0;j<8;j++){ 			//For loop to apply each byte to the CRC
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

//CRC lookup switch case statement
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

//a dot is a zero
//a dash is a one
//the bits are in reverse order 
//lsb first, msb last
//Switch case function to determine morse code from letter
struct let chooseemit(char a, struct let letter){		//Switch case function to set up morse code
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

//Initializes USART pins to talk to GPS
void initialize_USART(void){										//Set up pins for USART1
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE10)) | (GPIO_MODER_MODE10_1);	//SET to alt function mode
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE9)) | (GPIO_MODER_MODE9_1);
	GPIOA->AFR[1] = (GPIOA->AFR[1] & ~(0x00000FF0)) | (4 << (1 * 4)) | (4<<(2*4));	//Set to alt function for usart
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;																						//Turn on usart clock
	USART1->BRR = 160000 / 730; /* 9600 baud */
	USART1->CR1 = USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;																			//enable usart
}

//USART communication
void Transmit_Byte(char x){
	while((USART1->ISR & USART_ISR_TXE) == 0){
		;
	}
	USART1->TDR = x;
}

//Receives one byte from RDR register in USART1
char Receive_Byte(void){
	char x;
	USART1->ICR |= ((1 << 3));
	while((USART1->ISR & USART_ISR_RXNE) == 0){
		;
	}
		x = (uint8_t)(USART1->RDR); /* Receive data, clear flag */
	return x;
}

//Transmits GPS code, sends words with sizes of words stored in sizes array
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

//Transmit at seventeen words per minute
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

//Transmit at seven words per minute
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

//Transmits a Dash and turns off GPIO after
void dash(void) {
	GPIOA->ODR &= ~((1UL << 4));
	delayms(3 * ONEHUNDREDMS);
	
}

//Transmits a Dot and turns off GPIO after
void dot(void) {
	GPIOA->ODR &= ~((1UL << 4));
	delayms(ONEHUNDREDMS);
}

//Transmits a Dash at 7 words per minute
void dash7(void) {
	GPIOA->ODR &= ~((1UL << 4));
	delayms(3 * SEVENWPM);
	
}

//Transmits a Dot at 7 words per minute
void dot7(void) {
	GPIOA->ODR &= ~((1UL << 4));
	delayms(SEVENWPM - 0x300);
}

//Transmits a Dash at 17 words per minute
void dash17(void) {
	GPIOA->ODR &= ~((1UL << 4));
	delayms(3 * TEENWPM);
}

//Transmits a Dot at 17 words per minute
void dot17(void) {
	GPIOA->ODR &= ~((1UL << 4));
	delayms(TEENWPM);
}

//Delay function, will put microprocessor to sleep, one hundred ms has been defined
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

//Turns off the GPIO currently used to transmit
void Toggle_gpio(void){
	GPIOA->ODR |= ((1UL << 4));
	;
}

//Grab GPS data
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
	dmessage.size[0] = i;
	return dmessage;
}

//Grab GPS data
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

//Check if Balloon has landed or not
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
