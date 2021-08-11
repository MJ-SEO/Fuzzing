#include "Fuzzer.h" 

typedef struct fuzz_arg {
	int min_length;
	int max_length;
	int char_start;
	int char_range;
} fuzz_arg_t ;


Fuzzer rand_fuzzer ;
RandomFuzzer_init(&rand_fuzzer) ;
