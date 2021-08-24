#include "../include/mutating.h"

char*
delete_random_character(char* str, int length){
	if(length < 1) return NULL; 

	int pos;
	pos = rand()%length; // 0 ~ strlen(str)

	char* s = (char*)malloc(sizeof(char) * length + 1); // free?
	memcpy(s, str, length);
	s[pos] = 127;

	return s;
}

char*
insert_random_character(char* str, int length){
	int pos;
	pos = rand()%length; // 0 ~ strlen(str)

	char rand_char = rand()%95 + 32; // 32 ~ 127
	
	char* s = (char*)malloc(sizeof(char) * length + 2); // free?
	memcpy(s, str, sizeof(char) * length);

	s[pos] = rand_char;
	
	for(int i=pos+1; i<length+1; i++){
		s[i] = str[i-1];
	}

	return s;
}

char*
flip_random_character(char* str, int length){
	if(length < 1) return NULL;

	int pos;
	pos = rand()%length; // 0 ~ strlen(str)	
	
	char c = str[pos];	
	int bit; 
	bit = 1 << rand()%7;
	char new_c = c ^ bit;
//	printf("[DEBUG] Flip: %d in '%c' giving '%c'\n", bit, c, new_c);
	
	char* s = (char*)malloc(sizeof(char) * length + 2); // free?
	memcpy(s, str, sizeof(char) * length);
	s[pos] = new_c;

	return s;
}

char*
mutate(char* str, int inp_len){
	int mutators = rand()%3+1;
	char* mutate;
	if(mutators == 1){
		mutate = delete_random_character(str, inp_len);
	}
	else if(mutators == 2){
		mutate = insert_random_character(str, inp_len);
	}
	else{
		mutate = flip_random_character(str, inp_len);
	}

	return mutate;
}
