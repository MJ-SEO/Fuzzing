#ifndef CONFIG
#define CONFIG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINLEN 2
#define MAXLEN 4000
#define PATH_MAX 4096

typedef struct test_config{
	int f_min_len;
	int f_max_len;
	int f_char_start ; 
	int f_char_range ;

	char binary_path[PATH_MAX] ;

	char** cmd_args;

	int option_num;
	int trial;
	int timeout;
	int (* oracle) (char*, int, int*, int);
} test_config_t;

void config_init(test_config_t * config);

#endif
