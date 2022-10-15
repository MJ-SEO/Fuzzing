#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/fuzzer.h"

char*
fuzzer(int max_length, int start, int range){
	int len = rand()%(max_length + 1);
	char * out = (char *) malloc(sizeof(char) * len) ;
	for (int i = 0; i < len; i++) {
		out[i] = rand() % range + start ;
	}

	return out;
}
