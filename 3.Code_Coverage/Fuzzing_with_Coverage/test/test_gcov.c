#include "../include/fuzzer.h"
#include <dirent.h>
#include <sys/types.h>


void
config_setting(test_config_t* config){
	config->f_min_len = 10;
	config->f_max_len = 20;
	
	config->f_char_start = 32;
	config->f_char_range = 127;

	config->trial = 10;
	config->source = "cgi_decoder.c";

	strcpy(config->binary_path, "./decoder");
}

int main(){
	test_config_t config;

	config_init(&config);

	config_setting(&config);
	
	for(int i=0; i<100; i++){
		fuzzer_main(&config);
	}
}
