#include "../include/fuzzer.h"
#include <dirent.h>
#include <sys/types.h>


void
config_setting(test_config_t* config){
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
	config->source_path = "../lib/";
	config->curr_dir = 1;

	strcpy(config->binary_path, "./decoder");
}

int main(){
	test_config_t config;

	config_init(&config);

	config_setting(&config);
	
	fuzzer_main(&config);
}
