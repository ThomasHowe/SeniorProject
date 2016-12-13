/*!
 * @file ece406 encoder.h
 *
 * @brief ECE 406 Fall 2016 Senior Project "include" file
 *
 * @author Alan Kwok
 * @author Thomas Howe
 * 
 * @date December 12, 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include "stm32l0xx.h"                  // Device header
#include "stm32l053xx.h"

//Test code for waking up processor from WFI
//Also beep and sleep
void blinkledtest(void){
	int i;					//Counter
	GPIOA->ODR |= ((1UL << 4));		//GPIOA toggle 
	for(i=0;i<10;i++){			//Beep and sleep ten times
		GPIOA->ODR &= ~((1UL << 4));	//GPIOA toggle
		delayms(1 * ONEHUNDREDMS);	//Length of beep
		delayms(9 * ONEHUNDREDMS);	//Length of sleep
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
	int temp;							//Temporary value
	int j;								//Counter
	int i;								//Counter
	int step;
	for(i=0;i<length;i++){ 						//For loop to traverse through each byte
		for(j=0;j<8;j++){ 					//For loop to apply each byte to the CRC
			step = ((input[i] >> j) & 1) ^ (crcvalue & 1);
			crcvalue = crcvalue >> 1;			//Bit shift
			crcvalue = crcvalue & 0x7FFF;			//Set top bit to zero
			if(step){
				crcvalue = crcvalue ^ 0x8408;
			}
		}
	}
	crcvalue= ~crcvalue;
	for(i=0;i<4;i++){
		temp = (crcvalue >> (16 - (4+(4*i)))) & 0xF;
		result[i] = crclookup(temp);				//Allows to be transmitted as Morse code later
	}
	return result;
}

//CRC lookup switch case statement
//Returns char of value in Hexadecimal
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
			letter.letval = 2;			//10 in binary 
			letter.size = 2;			//Number of digits in binary
			return letter;
		}
		case 'B': {
			letter.letval = 1;			//0001 in binary
			letter.size = 4;			//Number of digits in binary
			return letter;
		}
		case 'C': {
			letter.letval = 5;			//01001 in binary
			letter.size = 4;			//Number of digits in binary
			return letter;
		}
		case 'D': {
			letter.letval = 1;			//0101 in binary
			letter.size = 3;			//Number of digits in binary
			return letter;
		}
		case 'E': {
			letter.letval = 0;			//0 in binary
			letter.size = 1;			//Number of digits in binary
			return letter;
		}
		case 'F': {
			letter.letval = 4;			//0100 in binary
			letter.size = 4;			//Number of digits in binary
			return letter;
		}
		case 'G': {
			letter.letval = 3;			//011 in binary
			letter.size = 3;			//Number of digits in binary
			return letter;
		}
		case 'H': {
			letter.letval = 0;			//0000 in binary
			letter.size = 4;			//Number of digits in binary
			return letter;
		}
		case 'I': {
			letter.letval = 0;			//00 in binary
			letter.size = 2;			//Number of digits in binary
			return letter;
		}
		case 'J': {
			letter.letval = 14;			//1110 in binary
			letter.size = 4;			//Number of digits in binary
			return letter;
		}
		case 'K': {
			letter.letval = 5;			//101 in binary
			letter.size = 3;			//Number of digits in binary
			return letter;
		}
		case 'L': {
			letter.letval = 2;			//0010 in binary
			letter.size = 4;			//Number of digits in binary
			return letter;
		}
		case 'M': {
			letter.letval = 3;			//11 in binary
			letter.size = 2;			//Number of digits in binary
			return letter;
		}
		case 'N': {
			letter.letval = 1;			//01 in binary
			letter.size = 2;			//Number of digits in binary
			return letter;
		}
		case 'O': {
			letter.letval = 7;			//111 in binary
			letter.size = 3;			//Number of digits in binary
			return letter;
		}
		case 'P': {
			letter.letval = 6;			//0110 in binary
			letter.size = 4;			//Number of digits in binary
			return letter;
		}
		case 'Q': {
			letter.letval = 11;			//1011 in binary
			letter.size = 4;			//Number of digits in binary
			return letter;
		}
		case 'R': {
			letter.letval = 2;			//010 in binary
			letter.size = 3;			//Number of digits in binary
			return letter;
		}
		case 'S': {
			letter.letval = 0;			//000 in binary
			letter.size = 3;			//Number of digits in binary
			return letter;
		}
		case 'T': {
			letter.letval = 1;			//1 in binary
			letter.size = 1;			//Number of digits in binary
			return letter;
		}
		case 'U': {
			letter.letval = 4;			//100 in binary
			letter.size = 3;			//Number of digits in binary
			return letter;
		}
		case 'V': {
			letter.letval = 8;			//1000 in binary
			letter.size = 4;			//Number of digits in binary
			return letter;
		}
		case 'W': {
			letter.letval = 6;			//110 in binary
			letter.size = 3;			//Number of digits in binary
			return letter;
		}
		case 'X': {
			letter.letval = 9;			//1001 in binary
			letter.size = 4;			//Number of digits in binary
			return letter;
		}
		case 'Y': {
			letter.letval = 13;			//1101 in binary
			letter.size = 4;			//Number of digits in binary
			return letter;
		}
		case 'Z': {
			letter.letval = 3;			//0011 in binary
			letter.size = 4;			//Number of digits in binary
			return letter;
		}
		case '1': {
			letter.letval = 30;			//11110 in binary
			letter.size = 5;			//Number of digits in binary
			return letter;
		}
		case '2': {
			letter.letval = 28;			//11100 in binary
			letter.size = 5;			//Number of digits in binary
			return letter;
		}
		case '3': {
			letter.letval = 24;			//11000 in binary
			letter.size = 5;			//Number of digits in binary
			return letter;
		}
		case '4': {
			letter.letval = 16;			//10000 in binary
			letter.size = 5;			//Number of digits in binary
			return letter;
		}
		case '5': {
			letter.letval = 0;			//00000 in binary
			letter.size = 5;			//Number of digits in binary
			return letter;
		}
		case '6': {
			letter.letval = 1;			//00001 in binary
			letter.size = 5;			//Number of digits in binary
			return letter;
		}
		case '7': {
			letter.letval = 3;			//00011 in binary
			letter.size = 5;			//Number of digits in binary
			return letter;
		}
		case '8': {
			letter.letval = 7;			//00111 in binary
			letter.size = 5;			//Number of digits in binary
			return letter;
		}
		case '9': {
			letter.letval = 15;			//01111 in binary
			letter.size = 5;			//Number of digits in binary
			return letter;
		}
		case '0': {
			letter.letval = 31;			//00000 in binary
			letter.size = 5;			//Number of digits in binary
			return letter;
		}
		case '.': {
			letter.letval = 42;			//101010 in binary
			letter.size = 6;			//Number of digits in binary
			return letter;
		}
		case '-': {
			letter.letval = 33;			//100001 in binary
			letter.size = 6;			//Number of digits in binary
			return letter;
		}
		case ',': {
			letter.letval = 51;			//110011 in binary
			letter.size = 6;			//Number of digits in binary
			return letter;
		}			
		case '+': {
			letter.letval = 10;			//01010 in binary
			letter.size = 5;			//Number of digits in binary
			return letter;
		}
		case '!': {
			letter.letval = 53;			//110101 in binary
			letter.size = 6;			//Number of digits in binary
			return letter;
		}
		case '$': {
			letter.letval = 33;			//100001 in binary
			letter.size = 6;			//Number of digits in binary
			return letter;
		}
		default : {
			//Error checking
			letter.size = 0;
			return letter;
		}
	}
}

//Initializes USART pins to talk to GPS
void initialize_USART(void){								//Set up pins for USART1
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE10)) | (GPIO_MODER_MODE10_1);	//SET to alt function mode
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE9)) | (GPIO_MODER_MODE9_1);	
	GPIOA->AFR[1] = (GPIOA->AFR[1] & ~(0x00000FF0)) | (4 << (1 * 4)) | (4<<(2*4));	//Set to alt function for usart
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;						//Turn on USART	clock				
	USART1->BRR = 160000 / 730; 							//9600 baud 
	USART1->CR1 = USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;			//Enable USART		
}

//USART communication
void Transmit_Byte(char x){
	while((USART1->ISR & USART_ISR_TXE) == 0){
		;					//Wait until flag is set
	}
	USART1->TDR = x;
}

//Receives one byte from RDR register in USART1
char Receive_Byte(void){
	char x;
	USART1->ICR |= ((1 << 3));
	while((USART1->ISR & USART_ISR_RXNE) == 0){
		;					//Wait until flag
	}
		x = (uint8_t)(USART1->RDR); /* Receive data, clear flag */
	return x;
}

//Transmits GPS code, sends words with sizes of words stored in sizes array
void transmitstring(char **message, int *sizes){
	int i, k, j;								//Counters
	struct let letter;
	for(i=0;i<5;i++){
		for(j=0;j<sizes[i];j++) {
				delayms(2 * ONEHUNDREDMS + 0x4000);		//
				letter = chooseemit(message[i][j], letter);	//Translate to Morse
				for(k=0;k<letter.size;k++) {			//size of letter as encoded in choose emit function
					if((letter.letval>>k)&1) dash();	//Check for dash if the value is one, it means a dash
					else dot();				//1 & 0 = 0, so its a dot
					delayms(1 * ONEHUNDREDMS);		//Length of a dot
				} 
		}
		delayms(4 * ONEHUNDREDMS);					//Space
	}
}

//Transmit at seventeen words per minute
void transmit17wpm(char **message, int *sizes){
	int i, k, j;								//Counters
	struct let letter;
	for(i=0;i<5;i++){
		for(j=0;j<sizes[i];j++) {
				delayms(2 * ONEHUNDREDMS + 0x15000);		//
				letter = chooseemit(message[i][j], letter);	//Translate to Morse
				for(k=0;k<letter.size;k++) {			//Size of letter as encoded in choose emit function
					if((letter.letval>>k)&1) dash17();	//Check for dash if the value is one, it means a dash
					else dot17();				//1 & 0 = 0, so its a dot
					delayms(1 * TEENWPM);			//Length of a dot
				} 
		}
		delayms(4 * ONEHUNDREDMS - 0x4000);				//Space
	}
}

//Transmit at seven words per minute
void transmitsevenwpm(char **message, int *sizes){
	int i, k, j;								//Counters
	struct let letter;
	for(i=0;i<5;i++){
		for(j=0;j<sizes[i];j++) {
				delayms(1 * ONEHUNDREDMS + 0x14000);		//
				letter = chooseemit(message[i][j], letter);	//Translate to Morse
				for(k=0;k<letter.size;k++) {			//Size of letter as encoded in choose emit function
					if((letter.letval>>k)&1) dash7();	//Check for dash if the value is one, if means a dash
					else dot7();				//1 & 0 = 0, so its a dot
					delayms(1 * SEVENWPM - 0x300);		//Length of a dot
				} 
		}
		delayms(4 * ONEHUNDREDMS);					//Space
	}
}

//Transmits a Dash and turns off GPIO after
void dash(void) {
	GPIOA->ODR &= ~((1UL << 4));
	delayms(3 * ONEHUNDREDMS);						//Length of 3 dot lengths
	
}

//Transmits a Dot and turns off GPIO after
void dot(void) {
	GPIOA->ODR &= ~((1UL << 4));
	delayms(ONEHUNDREDMS);							//Length of one hundred ms
}

//Transmits a Dash at 7 words per minute
void dash7(void) {
	GPIOA->ODR &= ~((1UL << 4));
	delayms(3 * SEVENWPM);							//Length of 3 dots at seven words per minute
	
}

//Transmits a Dot at 7 words per minute
void dot7(void) {
	GPIOA->ODR &= ~((1UL << 4));
	delayms(SEVENWPM - 0x300);						//Length of dots at seven words per minute
}

//Transmits a Dash at 17 words per minute
void dash17(void) {
	GPIOA->ODR &= ~((1UL << 4));
	delayms(3 * TEENWPM);							//Length of 3 dots at seventeen words per minute
}

//Transmits a Dot at 17 words per minute
void dot17(void) {
	GPIOA->ODR &= ~((1UL << 4));
	delayms(TEENWPM);							//Length of dot at seventeen words per minute
}

//Delay function, will put microprocessor to sleep, one hundred ms has been defined
void delayms(int time){
	SysTick->CTRL = 0;						//Clear systick control register to make sure it is off
	SysTick->LOAD = time;						//SET systick load to set time of systick timer
	NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);	//Turn on the interrupt
	SysTick->VAL = 0;						//clearer timer
	SysTick->CTRL |= 0x4;						
	SysTick->CTRL |= 0x1;
	SysTick->CTRL |= 0x2;						//Turn on systick timer
	__wfi();							//Set processor into sleep mode and will wake up when interupt occurs.
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
	
	//Used to check if the message is the right format
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
	//Wait until * and grab bytes over USART
	while(PONG[i] != '*'){
		i++;
		PONG[i] = Receive_Byte();
	}
	dmessage.data = PONG;
	dmessage.size[0] = i;
	return dmessage;
}

//Grab GPS data and parses it
struct gps parserer(char *pong){
	struct gps result;
	char message[60];				//Storage of GPS data
	int las=0, laf=0, los=0, lof=0, als=0, alf=0;	//initialization, check whether certain information has been obtained
	int i, j=0, k, size, ccount;			//Counters
	ccount = 0;					//Comma count
	size = 70;

	//',' is used to check where in the message the parserer is
	for(i=0;i<size;i++){
		if(pong[i] == ','){
			ccount++;
		}
		if(ccount == 2 && las == 0){
			las = i;			//Where the latitude information starts
		}
		if(ccount == 3 && laf == 0) laf = i;	//Where the latitude information ends
		if(ccount == 4 && los == 0) los = i;	//Where the longitude information starts
		if(ccount == 5 && lof == 0) lof = i;	//Where the longitude information ends
		if(ccount == 9 && als == 0) als = i;	//Where the altitude information starts
		if(ccount == 10 && alf == 0) alf = i;	//Where the altitude information ends
	}
	k=0;						//Set K to zero
	for(i = las+1; i<laf; i++){			//Storage of the latitude information
		message[j] = pong[i];
		result.lati[k] = pong[i];		//Store latitude in struct
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
	k=0;						//Reset K value
	for(i = los+1; i<lof; i++){			//Storage of longitude information
		message[j] = pong[i];
		result.longi[k] = pong[i];		//Store longitude in struct
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
	k=0;						//Reset K value
	for(i = als+1; i<alf; i++){			//Storage of altitude information
		message[j] = pong[i];
		result.alti[k] = pong[i];		//Store altitude in struct
		if(i == (alf-1)){
			message[j+1] = pong[i+2];
			j++;
		}
		j++;
		k++;
	}
	if(j < 5) return result;
	result.data = message;
	result.size[1] = j-1;				//Size of the GPS information
	return result;					//Return value that will be translated with emit and sent via Morse
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
