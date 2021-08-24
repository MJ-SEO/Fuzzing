#include "../include/fuzzer.h"

#include <dirent.h>
#include <sys/types.h>


void
config_setting(test_config_t* config){
	config->f_min_len = 10;
	config->f_max_len = 100;
	
	config->f_char_start = 0;
	config->f_char_range = 255;

	config->trial = 10;
	
	config->option_num = 1;
	char* option[1] = {"-b"};
	config->cmd_args = option;  

//	config->source = "my_troff.c";

	strcpy(config->binary_path, "./mytroff");
}

int main(){
	test_config_t config;

	config_init(&config);

	config_setting(&config);

	fuzzer_main(&config);
}
