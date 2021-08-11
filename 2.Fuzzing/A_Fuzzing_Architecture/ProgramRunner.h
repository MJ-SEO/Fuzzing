#include "runner.h"

typedef struct ProgramRunner {
	Runner runner;	
	char * sout; 
	char * serr; 
	int return_code; 
	char * program ;
	
	int (* run) (struct ProgramRunner *, char*, int);
	int (* run_process) (struct ProgramRunner *, char *, int) ;  
} ProgramRunner ;

void ProgramRunner_init (ProgramRunner* runner, char* program);
