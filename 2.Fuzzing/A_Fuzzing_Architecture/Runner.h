#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASS "PASS"
#define FAIL "FAIL"
#define UNRESOLVED "UNRESOLVED" 

typedef struct Runner {
	int input_size;
	char * input ;
	char * outcome ;

	int (*free_input) (struct Runner runner);	
	int (*run) (struct Runner *, char *, int) ;  // int : length of the input
} Runner ;

void Runner_init (Runner * runner) ;  // run 꼽아주기 

