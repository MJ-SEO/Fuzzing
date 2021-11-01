#include "../include/create_input.h"
#include "../include/mutating.h"

// #define DEBUG

#ifdef DEBUG
	#include "./mutating.c"
#endif

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
//	printf("[DEBUG] mutational_input fname: %s\n", input_file);
	if(fp == NULL){
		perror("mutationl_input: File open failed");
		exit(1);
	}
	

	int len = 0;
	char* seed = (char*)malloc(sizeof(char) * SEED_MAX);
	memset(seed, 0, SEED_MAX);
	while((seed[len] = getc(fp)) != EOF){
		len++;
	}
	
//	printf("[DEUBG] seed(%d): %s\n", len, seed);
	strcpy(fuzz, seed);

	for(int i=0; i<trial; i++){
		len = mutate(seed, fuzz, len);
		strcpy(seed, fuzz);
#ifdef DEBUG
		printf("[%d] Fuzz(%d): %s\n", i, len, fuzz);
#endif
	}

	free(seed);
	fclose(fp);
	return len;
}

/*

int		// TEST DRIVER for create_input
main(){
	srand((unsigned int)time(NULL));
	char* fuzzed_input = (char*)malloc(sizeof(char) * 1024);
	
	int len = mutational_input(fuzzed_input, "./input1", 10);
	
	printf("[DEBUG] result(%d): %s\n", len, fuzzed_input);	
}
*/

