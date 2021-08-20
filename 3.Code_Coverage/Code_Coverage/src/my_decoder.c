#include "../include/my_decoder.h"

int
hex_value(char hex_char){
	if(isdigit(hex_char)){
		return hex_char-48;
	}
	else{
		return tolower(hex_char)-87;
	}
}

char*
cgi_decode(char* str){
	char* s = (char*)malloc(sizeof(char) * strlen(str));
	int k=0;
	for(int i=0; i<strlen(str); i++){
		if(str[i] == '+'){
			s[k] = ' ';
			k++;
		}
		else if(str[i] == '%'){
			char digit_high = str[i+1];
			char digit_low = str[i+2];
			if(isxdigit(digit_low) && isxdigit(digit_high)){
				int value = hex_value(digit_high)*16 + hex_value(digit_low);
				s[k] = value;	
				i+=2;
			}
			else{
				perror("Invalid encoding!");
				return 0x0;
			}
		}
		else{
			s[k] = str[i];
			k++;
		}
	}

	return s;
}


