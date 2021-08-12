#ifndef CREATE_INPUT 
#define CREATE_INPUT

#include "config.h"

int RandomeFuzzer(int min_len, int max_len, int start, int range);

int create_input(test_config_t * config, char* input);

#endif
