#ifndef CGI
#define CGI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hex_values[256];

void init_hex_values(); 

int cgi_decode(char *s, char *t);

#endif
