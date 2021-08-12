#include "fuzzer.h"
#include "create_input.h"
#include "run.h"
// #include <sys/stat.h>

test_config_t tconfig;

void
fuzzer_init(test_config_t * config){
	/*
	   1. check some conditions
		   - binary path validity
		   - default values
	   2. make result directory
	 */
	
	printf("Fuzzer Init\n");

	if(mkdir("test_dir") == -1){
		perror("mkdir Failed\n");
		exit(1);
	}	

}

void
fuzzer_main(){
	for(int i = 0; i < config.trial; i++){
		char * input = create_input(&config);
		run(&config, input);
		oracle(dir_name);	
	}
}
