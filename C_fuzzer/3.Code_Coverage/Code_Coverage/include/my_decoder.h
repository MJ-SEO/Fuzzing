#ifndef CGI
#define CGI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int hex_value(char hex_char);

char* cgi_decode(char* str);

#endif
