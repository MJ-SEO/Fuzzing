#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "../fuzzer.h"

char*
heartbeat(char* reply, int length, char* mem){
	char* temp = (char*)malloc(sizeof(char) * 2500);
	strcpy(temp, reply);
	strcat(temp, mem);
	mem = temp;	
	free(temp);

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

	printf("%s\n", heartbeat("potato", 6, secrets));

	for(int i=0; i<10; i++){
		char* s = (char*)malloc(sizeof(char) * 2500);
		s = heartbeat(fuzzer(MAX_LEN, START, RANGE), rand()%500+1, secrets);
		assert(!(strstr(s, uninitialized_memory_marker) != NULL));
		assert(!(strstr(s, "secret") != NULL));
		free(s);
	}

	free(secrets);
	return 0;
}
