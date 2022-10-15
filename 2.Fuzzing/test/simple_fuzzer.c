#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/fuzzer.h"

char*
fuzzer(int max_length, int start, int range){
	int len = (rand()%max_length+1)+1;
	char* out = (char*)malloc(sizeof(char) * len);
	for(int i=0; i<len; i++){
		out[i] = (char)((rand()%range) + start);
	}
	out[len-1] = '\0';
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
