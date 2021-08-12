#include "config.h"

void 
config_init(test_config_t * config){
    config->f_min_len = 10 ;
    config->f_max_len = 100 ;
    config->f_char_start = 32 ;
    config->f_char_range = 32 ;

    strcpy(config->binary_path, "") ;
    
    config->cmd_args = 0x0 ; 
   
    config->trial = 10 ; 

    config->timeout = 5 ; 

    config->oracle = 0x0 ;    
}
