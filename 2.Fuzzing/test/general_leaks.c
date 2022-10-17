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

char*
heartbeat(char* reply, int length, char* mem){
	strncpy(mem, reply, strlen(reply));
	
	char* str = (char*)malloc(sizeof(char) * length+1);
	strncpy(str, mem, length);
	return str;
}

int main(){
	srand((unsigned int)time(NULL));
	char* secrets = (char*)malloc(sizeof(char) * 2500);
	sprintf(secrets, "<space for reply> %s <secret-certificate> %s <secret-key> %s <other-secrets>\n", fuzzer(MAX_LEN, START, RANGE), fuzzer(MAX_LEN, START, RANGE), fuzzer(MAX_LEN, START, RANGE));
	
	char* uninitialized_memory_marker = "deadbeef";
	while(strlen(secrets) < 2048){
		strcat(secrets, uninitialized_memory_marker);
	}	

	printf("%s\n", heartbeat("POTATO", 6, secrets));
	printf("%s\n", heartbeat("BIRD", 4, secrets));
	printf("%s\n", heartbeat("HAT", 500, secrets));

	for(int i=0; i<10; i++){
		char* s = (char*)malloc(sizeof(char) * 2500);
		s = heartbeat(fuzzer(MAX_LEN, START, RANGE), rand()%500+1, secrets);
		assert((strstr(s, uninitialized_memory_marker) == NULL));
		assert((strstr(s, "secret") == NULL));
		free(s);
	}

	free(secrets);
	return 0;
}

