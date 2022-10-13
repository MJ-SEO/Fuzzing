#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "bugs.h"

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

