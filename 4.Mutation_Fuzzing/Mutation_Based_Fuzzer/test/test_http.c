#include "../include/fuzzer.h"
#include <dirent.h>
#include <sys/types.h>


void
config_setting(test_config_t* config){
	config->mutation_dir = "./input/http_inp";
	config->mutation = 1;

	config->trial = 50;

	config->source = "http_program.c";
	config->source_path = "../lib/http_program.c";

	strcpy(config->binary_path, "./http_mutation");
}

int main(){
	test_config_t config;

	config_init(&config);

	config_setting(&config);

	fuzzer_main(&config);
}
