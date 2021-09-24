#ifndef HTTPPROG
#define HTTPPROG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

typedef struct url{
	int url_status;
	char schema[10];
	char netloc[50];
	char path[150];
	char query[30];
	char fragment[30];
} url_t;

url_t* url_parser(char* target_url);

int http_program(char* target_url);

int is_valid_url(char* target_url);

#endif
