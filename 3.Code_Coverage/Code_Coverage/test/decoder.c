#include "../include/cgi_decoder.h"

int main(int argc, char *argv[]) {
	init_hex_values();

	if (argc >= 2) {
		char *s = argv[1];
		char *t = malloc(strlen(s) + 1); /* output is at most as long as input */
		int ret = cgi_decode(s, t);
		printf("%s\n", t);
		return ret;
	}
	else
	{
		printf("cgi_decode: usage: cgi_decode STRING\n");
		return 1;
	}
}
