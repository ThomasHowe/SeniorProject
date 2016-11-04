#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	//char pong[80] = "GPGGA,202410.000,4042.6000,N,07400.4858,W,1,4,3.14,276.7,M,-34.2,M,,*63";
	char pong[80] = "GPGGA,,,,,,0,,,,,,,,*63";
	char message[60];
	int las=0, laf=0, los=0, lof=0, als=0, alf=0;
	int i, j, size, ccount;
	ccount = 0;
	size = 70;

	for(i=0;i<size;i++){
		if(pong[i] == ','){
			ccount++;
			printf("%d\n", ccount);
		}
		if(ccount == 2 && las == 0){
			las = i;
			printf("%d\n", las);
		}
		if(ccount == 3 && laf == 0) laf = i;
		if(ccount == 4 && los == 0) los = i;
		if(ccount == 5 && lof == 0) lof = i;
		if(ccount == 9 && als == 0) als = i;
		if(ccount == 10 && alf == 0) alf = i;
	}
	printf("hello there\n");
	if((laf-las) == 1){
			printf("oh no\n");
	}
	for(i = las+1; i<laf; i++){
		message[j] = pong[i];
		if(i == (laf-1)){
			message[j+1] = pong[i+2];
			j++;
		}
		j++;
	}
	for(i = los+1; i<lof; i++){
		message[j] = pong[i];
		if(i == (lof-1)){
			message[j+1] = pong[i+2];
			j++;
		}
		j++;
	}
	for(i = als+1; i<alf; i++){
		message[j] = pong[i];
		if(i == (alf-1)){
			message[j+1] = pong[i+2];
			j++;
		}
		j++;
	}
	for(i=0; i<j; i++){
		printf("%c", message[i]);
	}
	return 0;
}
