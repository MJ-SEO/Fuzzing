#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char*
fuzzer(int max_length, int start, int range){
	int strlen = (rand()%max_length+1)+1;
	char* out = (char*)malloc(sizeof(char) * strlen);
	for(int i=0; i<strlen; i++){
		out[i] = (char)((rand()%range) + (start+range)); 
	}
	return out;	
}

int ord(char ascii){
	return (int)ascii;
}

int main(){
	srand((unsigned int)time(NULL));
	char* mystr;
	
	mystr = fuzzer(1000, ord('a'), 26);

	int i = 0;
	for(int i=0; i<1000; i++){
		printf("%c", mystr[i]);
	}
	printf("\n");
	return 0;
}
