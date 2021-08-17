#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int hex_values[256];

void init_hex_values() {
	for (int i = 0; i < sizeof(hex_values) / sizeof(int); i++) {
		hex_values[i] = -1;
	}
	hex_values['0'] = 0; hex_values['1'] = 1; hex_values['2'] = 2; hex_values['3'] = 3;
	hex_values['4'] = 4; hex_values['5'] = 5; hex_values['6'] = 6; hex_values['7'] = 7;
	hex_values['8'] = 8; hex_values['9'] = 9;

	hex_values['a'] = 10; hex_values['b'] = 11; hex_values['c'] = 12; hex_values['d'] = 13;
	hex_values['e'] = 14; hex_values['f'] = 15;

	hex_values['A'] = 10; hex_values['B'] = 11; hex_values['C'] = 12; hex_values['D'] = 13;
	hex_values['E'] = 14; hex_values['F'] = 15;
}

int cgi_decode(char *s, char *t) {
	while (*s != '\0') {
		if (*s == '+')
			*t++ = ' ';
		else if (*s == '%') {
			int digit_high = *++s;
			int digit_low = *++s;
			if (hex_values[digit_high] >= 0 && hex_values[digit_low] >= 0) {
				*t++ = hex_values[digit_high] * 16 + hex_values[digit_low];
			}
			else
				return -1;
		}
		else
			*t++ = *s;
		s++;
	}
	*t = '\0';
	return 0;
}

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
