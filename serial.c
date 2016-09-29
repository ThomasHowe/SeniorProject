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
  for(i=0;i<100;i++){
      transmit(100);
      usleep(900000);
  }
  if (!GPS_Status(long,lat,alt)){
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
    }
} 

void parse(){
   int i = 0;
   int n = 1;
   if(char[0] == 'G' && char[1] == 'P' && char[2] == 'G' && char[3] == 'G' && char[4] == 'A'){  //Checks to make sure its GPGGA msg
      for(i=0; i<Sizeof(char);i++)                                                              //Traverses entire message
          if (char[i] == ',') count++;                                                          //counts number of commas they are separators
          if(count == 2){                                                                       //if comma count is 2, get lattitude
             while(char[i+n] != ','){                                                           //go until hits next comma
                lat[n] = char[i+n];
                n++;
                if(char[i+n] == ',') lat[n+1] = char[i+n+1];                                    //Adds direction of coordinates
             }
             i = i+n;                                                                           //Move to i+n in message and
             count = 3;                                                                         //increment comma count
          }
   }
}
}
