#include "../include/fuzzer.h"
#include <dirent.h>
#include <sys/types.h>


void
config_setting(test_config_t* config){
	//config->f_min_len = 10;
	//config->f_max_len = 20;
	
	//config->f_char_start = 32;
	//config->f_char_range = 127;

	config->mutation_dir = "./input/cgi_inp";
	config->mutation = 1;

	config->trial = 100;

	config->number_of_source = 1;
	
	char** src_arr = (char**)malloc(sizeof(char*) * 1);	// TODO free
	for(int i=0; i<1; i++){
		src_arr[i] = (char*)malloc(sizeof(char) * 1024);
	}
	
	src_arr[0] = "cgi_decoder.c";

	config->sources = src_arr;
	config->source_path = "../lib/cgi_decoder.c";

	strcpy(config->binary_path, "./decoder");
}

int main(){
	test_config_t config;

	config_init(&config);

	config_setting(&config);
	
	fuzzer_main(&config);
}
