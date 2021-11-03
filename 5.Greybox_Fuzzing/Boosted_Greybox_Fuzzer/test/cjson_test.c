#include "../include/fuzzer.h"
#include <dirent.h>
#include <sys/types.h>

void
config_setting(test_config_t* config){
	config->mutation_dir = "./input/cjson_inp";
	config->mutation = 1;

	config->trial = 200000;

	int n_src = 1;
	config->number_of_source = n_src;

	char** src_arr = (char**)malloc(sizeof(char*) * n_src);
	for(int i =0; i<n_src; i++){
		src_arr[i] = (char*)malloc(sizeof(char) * 1024);
	}

	src_arr[0] = "cJSON.c";

	config->greybox = 1;
	config->sources = src_arr;
	config->source_path = "../lib/CJSON/";
	config->curr_dir = 1;

	strcpy(config->binary_path, "./cjson");
}

int main(){
	test_config_t config;

	config_init(&config);

	config_setting(&config);
	
	fuzzer_main(&config);
}
