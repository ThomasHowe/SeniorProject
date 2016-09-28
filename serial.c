#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize_pins(void); //Initialize Serial Pins to RX/TX modes
char *Receive_Coordinates(void); //Receives the string from GPS
int GPS_Status(char *long, char *lat, char *alt);
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

int GPS_Status(char *longi, char *lat, char *alt){
   //Check if GPS is on or off already
   //Altitude Checking
   //Check to see if coord are same as last time
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
