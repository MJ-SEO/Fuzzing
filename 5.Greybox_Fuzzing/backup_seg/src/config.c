#include "../include/config.h"

int
default_oracle(char* dir_name, int file_num, int* result, int return_code){
	if(return_code == 0) return 0;
	else return -1;
}

void 
config_init(test_config_t * config){
    config->f_min_len = 4 ;
    config->f_max_len = 4 ;
    config->f_char_start = 32 ;
    config->f_char_range = 96 ;

    config->mutation_dir = 0x0;
    config->mutation = 0;
    config->exponent = 5;

    strcpy(config->binary_path, "") ;
   
    config->need_args = 0; 
    config->cmd_args = 0x0;
    
    config->option_num = 0;

    config->sources = 0X0;
    config->source_path = 0X0;
    config->number_of_source = 0;
    config->curr_dir = 1;

    config->trial = 10 ; 

    config->timeout = 4 ; 

    config->oracle = default_oracle ;    
}

