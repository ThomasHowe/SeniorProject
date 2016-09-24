#include <stdio.h>
#include <sys/io.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/ioctl.h>
#include <errno.h>

//struct that determines how many
//times bit shifts occur 
//based upon the letter. 
struct let{
	int size;
	int letval;
};

//function that sets the values for the struct
struct let chooseemit(char a, struct let letter);
void dash(int fd, int bitset);
void dot(int fd, int bitset);

int main(int argc, char *argv[]){
	int i = 0;
	int j = 0, fd;
	int k = 0, bitset = TIOCM_DTR;
	int serial;
	struct let letter;
	fd = open("/dev/ttyUSB0", O_RDWR);
	if(fd == -1){
   	 	printf("open_port: Unable to open /dev/ttyUSB0 - ");
		exit(1);
  	}

	ioctl(fd, TIOCMGET, &serial);
	ioctl(fd, TIOCMSET, &bitset);		//Turn led off one second
	sleep(1);
	if (argc != 2) {
		printf("not correct number of arguments, use only 1 string as message\n");
		return 1;
	}
	else if(argc == 2) {
		for(k=0;k<strlen(argv[1]);k++) {
			letter = chooseemit(argv[1][k], letter);
			for(j=0;j<letter.size;j++) {
				if((letter.letval>>j)&1) dash(fd, bitset);
				else dot(fd, bitset);
			} 
		}
	}
	return 0;
}

//a dot is a zero
//a dash is a one
//the bits are in reverse order 
//of how you would expect
//them to be transmitted
//lsb first, msb last
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
			printf(“Only lower case letters no spaces”);
			exit(2);			//error checking
	}
}

//sleep for a second with led on
//then sleep for a half second with led off
void dash(int fd, int bitset) {
	ioctl(fd, TIOCMBIC, &bitset);	//Led on
	sleep(1);
	ioctl(fd,TIOCMSET, &bitset);	//Led off
	usleep(500000);
}

//sleep for half second with led on
//sleep for half second with led off
void dot(int fd, int bitset) {
	ioctl(fd, TIOCMBIC, &bitset);	//Led on
	usleep(500000);
	ioctl(fd, TIOCMSET, &bitset);	//Led off
	usleep(500000);
}
