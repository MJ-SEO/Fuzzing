#include "create_input.h"

char*
RandomFuzzer(int min_len, int max_len, int start, int range){
	int len = rand()%(max_len - min_len + 1) + min_len;
	char* out = (char*)malloc(sizeof(char) * (len + 1));
	for(int i=0; i<len; i++){
		out[i] = rand()%(range + 1) + start;
	}
	out[len] = '\0';
	return out;
}

char* 
create_input(test_config_t * config){
	return RandomFuzzer(config->f_min_len, config->f_max_len, config->f_char_start, config->f_char_range);	
}
