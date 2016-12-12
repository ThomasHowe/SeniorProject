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
		temp = crcvalue>>((16 - (4+(4*i))) & 0xF);
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
