#include "../include/create_input.h"
#include "../include/mutating.h"
#include "../src/mutating.c" // ...

int
RandomFuzzer(int min_len, int max_len, int start, int range, char* fuzz){
	int len = rand()%(max_len - min_len + 1) + min_len;
	for(int i=0; i<len; i++){
		fuzz[i] = rand()%(range + 1) + start;
	}
	fuzz[len] = '\0';
	
	return len;
}

int 
create_input(test_config_t * config, char* fuzz){
	return RandomFuzzer(config->f_min_len, config->f_max_len, config->f_char_start, config->f_char_range, fuzz);	
}

int 
mutational_input(char* fuzz, char* input_file, int trial){
	FILE* fp;
	fp = fopen(input_file, "rb");
	if(fp == NULL){
		perror("mutationl_input: File open failed");
		exit(1);
	}

	int len = 0;
	char* seed = (char*)malloc(sizeof(char) * 1024);	// TODO realloc?
	while((seed[len] = getc(fp)) != EOF){
		len++;
	}

	for(int i=1; i<=trial; i++){
		strcpy(seed, mutate(seed, len));	// TODO Mutate len
	//	if(i%5 == 0) printf("[DEUBG] %d mutatations: %s\n", i, seed);
	}
	strcpy(fuzz, seed);

	free(seed);
	fclose(fp);
	return len;
}