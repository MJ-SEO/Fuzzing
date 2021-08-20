#ifndef READGCOV
#define READGCOV

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct coverage{
	char c_file[64];
	int line_number;
} coverage_t;

void
read_gcov_coverage(char* c_file);

#endif
