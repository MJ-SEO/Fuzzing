#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define MAX_LEN 100
#define START 32
#define RANGE 32

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

void
crash_if_too_long(char* str, char* buffer){
	assert(strlen(str) < strlen(buffer));
}

int
hang_if_no_space(char* str){
	int i=0;
	time_t start, end;
	start = clock();
	while(1){
		if(i < strlen(str)){
			if(str[i] == ' ') return -1;
			i++;
		}
		end = clock();
		if((double)(end-start)/CLOCKS_PER_SEC > 1) break;
	}
	return i;
}

void
collapse_if_too_large(char* str){
	assert(atoi(str) < 1000);
}

void 
buffer_overflows(){
	for(int i=0; i<100; i++){
		char* data = fuzzer(MAX_LEN, START, RANGE);
		crash_if_too_long(data, "Thrusdayyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy");
	}
}

void
missing_error_check(){
	for(int i=1; i<=100; i++){
		char* data = fuzzer(MAX_LEN, START, RANGE);
//		printf("[DEBUG] %s\n", data);
		if(hang_if_no_space(data) == -1){
			printf("[%d] Hang_if_no_space\n", i);	
		}
	}
}

void
rogue_number(){
	for(int i=0; i<100; i++){
		char* data = fuzzer(2, 48, 10);
		//printf("[DEBUG] %s\n", data);
		collapse_if_too_large(data);
	}
}


int main(){
	srand((unsigned int)time(NULL));
//	buffer_overflows();
	missing_error_check();
//	rogue_number();
	return 0;
}
