#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize_pins(void); //Initialize Serial Pins to RX/TX modes
char *Receive_Coordinates(void); //Receives the string from GPS
int GPS_Status(char *long, char *lat, char *alt);
void transmit_coord(char *message);

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
  //Write Code to Parse GPS Packet
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
