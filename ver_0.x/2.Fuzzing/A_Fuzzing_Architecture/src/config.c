#include "../include/config.h"

int
default_oracle(char* dir_name, int file_num, int* result, int return_code){
	if(return_code == 0) return 0;
	else return -1;
}

void 
config_init(test_config_t * config){
    config->f_min_len = 10 ;
    config->f_max_len = 100 ;
    config->f_char_start = 32 ;
    config->f_char_range = 32 ;

    strcpy(config->binary_path, "") ;
    
    config->cmd_args = 0x0;
    
    config->option_num = 0;

    config->is_source = 0;
    config->source = 0X0;

    config->trial = 10 ; 

    config->timeout = 4 ; 

    config->oracle = default_oracle ;    
}

