#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../fuzzer.h"
#include "bugs.h"

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
