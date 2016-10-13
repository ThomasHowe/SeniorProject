#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize_pins(void); //Initialize Serial Pins to RX/TX modes
char *Receive_Coordinates(void); //Receives the string from GPS
int GPS_Status(char *longi, char *lat, char *alt, int count);
void transmit_coord(char *message);
void parse(void);

int main(){
  int i;
  int count = 0;
  char longi = 0;
  char lat = 0; 
  char alt = 0;
  for(i=0;i<100;i++){
      transmit(100);
      usleep(900000);
  }
  if (!GPS_Status(longi,lat,alt,count)){
      //Toggle Transistor to cut power to GPS
      //Save Last measured Coord to be sent periodically
  }
  packet = Receive_Coordinates();
  parse();
  transmit_coord(transmission);
  
}

void initialize_pins(void){
//Set up CC1101 into CW Mode
//Set up GPS to get fix and go to low power mode
//Set up pins for Serial Comm/Toggling battery to GPS on/CC1101 Toggling
//Clock for GPIOA
RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
//Configure GPIO for MOSI,MISO, and SCK pins
//PA4,5,6,7
//PA4=NSS
//PA5=SCK
//PA6=MISO
//PA7=MOSI
GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE4)) | (GPIO_MODER_MODE4_1);
GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE5)) | (GPIO_MODER_MODE5_1);
GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE6)) | (GPIO_MODER_MODE6_1);
GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE7)) | (GPIO_MODER_MODE7_1);
//GPIOA->AFRL is already set to what is needed
GPIOA->AFRL &= (0xFFFF0000);
//Write to SPI_CR1 register
SPI1->CR1 = SPI_CR1_MSTR | SPI_CRI_BR;		//Configure CPOL and CPHA at zero to rising edge
SPI1->CR2 = SPI_CR2_SSOE | SPI_CR2_RXNEIE;	//Slave select enabled, 8-bit Rx fifo
SPI1->CR1 |= SPI_CR1_SPE;			//Enable the SPI1
//Select simplex or half-simplex configure RXONLY or BIDIMODE	
	
//Set up GPS USART Communication
USART1->BRR = 160000 / 96; 		  //9600 baud
USART1->CR1 = USART_CR1_TE | USART_CR1_UE //8 data bit, 1 start bit, 1 stop bit, no parity
  
}

char *Receive_Coordinates(void) {
   volatile char packet1[128];
   volatile char packet2[128];
	
   volatile char *rearbuffer;
   volatile char *activebuffer;
	
   volatile char pointer = 0;
   
   activebuffer = packet1;
   rearbuffer = packet2;
   systick {
      if(finishflag) {
	   int finishflag = 1;
	   int currentsample = 0;
	   rearbuffer[currentsample] = something;
	   if(currentsample < 128) {
	       //start sampling what GPS is currently sending
	       //Recieve byte
	       //Will need to be fixed later, place HOLDER
	       rearbuffer = (uint8_t)(USART1->RDR);  
	   }
	   else {
		currentsample = 0;
		finishflag = 0;
	   }
      }
   }
}

int GPS_Status(char *longi, char *lat, char *alt, int count){
   //Check if GPS is on or off already
   //Altitude Checking
   //Check to see if coord are same as last time
  
   int state = 1;
   //Check if GPS is on or off already
   //if state is 1, the GPS is on
   //if state is 0, GPS is off
   //arrays storing all the values from the 
   char longis[100];
   char lats[100];
   char alts[100];
   //Check if the altitude is low and if the location is the same
   //if they are not the same, the alt and loc are 0
   //if they are the same, alt and loc are 1
   lowalt = 0;
   samealt = 0;
   sameloc = 0;

   If (state == 1) {
	//add to what is currently in arrays
	longis[count] = longi;
	lats[count] = lat;
	alts[count] = alt;
	//Altitude Checking
	if (5000 < alt) {
		lowalt = 1;
	}
	if (alts[count] == alts[count-1] {
		samealt = 1;
	}
	//Check to see if coord are the same as last time
	if ((longis[count] == longis[count-1]) && (lats[count] == lats[count-1])) {
		sameloc = 1;
	}
	if ((lowalt == 1) && (samealt == 1) && (sameloc == 1)) {
		//Set pins so that GPS is shut off
		//Set state to zero
		state = 0;
	}
    }
} 

void parse(){
   int i = 0;
   int n = 1;
   if(char[0] == 'G' && char[1] == 'P' && char[2] == 'G' && char[3] == 'G' && char[4] == 'A'){  //Checks to make sure its GPGGA msg
      for(i=0; i<Sizeof(char);i++){                                                             //Traverses entire message
          if (char[i] == ',') count++;                                                          //counts number of commas they are separators
          if(count == 2){                                                                       //if comma count is 2, get lattitude
             while(char[i+n] != ','){                                                           //go until hits next comma
                lat[n] = char[i+n];
                n++;
                if(char[i+n] == ',') lat[n+1] = char[i+n+1];                                    //Adds direction of coordinates
             }
             i = i+n;                                                                           //Move to i+n in message and
	     count++;
	  }
	  if(count == 4){
	     while(char[i+n] != ','){								//increment comma count
   		long[n] = char[i+n];
		n++;
		if(char[i+n] == ',') long[n+1] = char[i + n + 1];
	     }
	     i = i+n
	     count++;
	  }
	  if(count == 9){									//9 commas and we are at alt
		  while(char[i+n] != ','){
			  alt[n] = char[i+n];
			  n++;
		  }
	  i = i+n;
	  count++;
   }
}
}
