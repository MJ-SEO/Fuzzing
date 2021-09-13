#ifndef CONFIG
#define CONFIG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MINLEN 2
#define MAXLEN 4000
#define PATH_MAX 4096

typedef struct test_config{
	// configuations for random fuzzer input
	int f_min_len;
	int f_max_len;
	int f_char_start ; 
	int f_char_range ;

	// configuations for mutaional fuzzer input
	int mutation;
	char* mutation_dir; // Dir path for mutation input seeds
	
	char binary_path[PATH_MAX] ; // bin path of target executeion file

	// configuations for gcov
	char** sources;
	char* source_path;	// path of sources
	int number_of_source;
	int curr_dir; 	// 0: target sources are in same directory
			// 1: target sources are in different directory path

	// configuations for command line args
	int need_args;
	char** cmd_args;

	int option_num;
	int trial;
	int timeout;
	int (* oracle) (char*, int, int*, int);
} test_config_t;

void config_init(test_config_t * config);

#endif
