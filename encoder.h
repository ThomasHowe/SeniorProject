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

#ifndef ENCODER.H
#define ENCODER.H

//Struct used to determine what character something is and how it should be transmitted in Morse
struct let{
	int size;
	int letval;
};

//Struct for GPS data
struct gps{
	char longi[10];
	char lati[10];
	char alti[10];
	char *data;
	char *preparsedata;
	int size[3];
};

void initialize_USART(void);				//Initializes USART pins to talk to GPS
char Receive_Byte(void);				//Receives one byte from RDR register in USART1				
void transmitsevenwpm(char **message, int *sizes);	//Transmit at seven words per minute
char crclookup(int value);				//Lookup switch case statement 
void transmit17wpm(char **message, int *sizes);		//Transmit at seventeen words per minute
int GPScheck(char *oldalti, char *newalti, int status); //Check if Balloon has landed or not
char * crc(char *input, int length);			//Calculate CRC value
struct gps parserer(char *pong);			//Grab GPS data and parses it
struct gps Parser(void);				//Grab GPS data and passes to parserer
void Transmit_Byte(char x);				//USART communication
void blinkledtest(void);				//Test code for waking up processor from WFI
void transmitstring(char **message, int *sizes);	//Transmits GPS code, sends words with sizes of words stored in sizes array
void dot(void);						//Transmits a Dot and turns off GPIO after
void dot7(void);					//Transmits a Dot at 7 words per minute
void dot17(void);					//Transmits a Dot at 17 words per minute
void dash(void);					//Transmits a Dash and turns off GPIO after
void dash7(void);					//Transmits a Dash at 7 words per minute
void dash17(void);					//Transmits a Dash at 17 words per minute
void Toggle_gpio(void);					//Turns off the GPIO currently used to transmit
void delayms(int time);					//Delay function, will put microprocessor to sleep, one hundred ms has been defined
void SleepUsart(void);					//Currently not implemented, will put GPS to sleep mode to save power
struct let chooseemit(char a, struct let letter);	//Switch case function to determine morse code from letter

#endif
