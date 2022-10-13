#ifndef FUZZER
#define FUZZER

#include "create_input.h" // config.h

void fuzzer_init(test_config_t *config, char* dir_name, int* flag);

void fuzzer_main(test_config_t *config);

#endif
