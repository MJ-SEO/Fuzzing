#include <time.h>
#include "ProgramRunner.h"

typedef struct Fuzzer {
	char * (fuzz *) (int *) ; // char * fuzz(int * length)
	void (* run) (void (runner *) (Runner *, char *, int)); 
	void (* runs) (void (print_runner *) (Runner *, char *, int), int); 
} Fuzzer ;

void Fuzzer_init (Fuzzer * fuzzer) ;
