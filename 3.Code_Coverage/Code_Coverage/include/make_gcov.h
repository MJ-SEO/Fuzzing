#ifndef MAKECGI
#define MAKECGI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void 
compile_cgi(char* target, char* fname);

void
exec_cgi(char* fname, char* args);

void
exec_gcov(char* target);

void
make_gcov(char* c_file, char* fname, char* args);

#endif
