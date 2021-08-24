#include "../include/create_input.h"

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
create_input(test_config_t * config, char* fuzz){
	
}
