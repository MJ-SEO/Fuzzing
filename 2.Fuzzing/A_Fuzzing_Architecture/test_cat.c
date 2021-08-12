#include "fuzzer.h"

int 
oracle(char* dir_name){
	printf("Hello oracle\n");
}

void
config_setting(test_config_t* config){
	config->f_min_len = 1030;
	config->f_max_len = 1030;
	config->f_char_start = 32;
	config->f_char_range = 32;

	strcpy(config->binary_path, "/bin/cat");

	config->trial = 10;
	config->timeout = 5;

	config->oracle = oracle;
}

int main(){
	test_config_t config;
	
	config_init(&config);

	config_setting(&config);
	
//	printf("[DEBUG] %d %d %d %d %s %d %d\n", config.f_min_len, config.f_max_len, config.f_char_start, config.f_char_range, config.binary_path, config.trial, config.timeout);
	
	fuzzer_main(&config);
}
