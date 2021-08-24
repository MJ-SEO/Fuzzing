#include "../include/mutating.h"

char*
delete_random_character(char* str){
	if(str == NULL) return NULL; // TODO strlen

	int pos;
	pos = rand()%strlen(str); // 0 ~ strlen(str)

	char* s = (char*)malloc(sizeof(char) * strlen(str) + 1); // free?
	memcpy(s, str, strlen(str));
	s[pos] = 127;

	return s;
}

char*
insert_random_character(char* str){
	int pos;
	pos = rand()%strlen(str); // 0 ~ strlen(str)

	char rand_char = rand()%95 + 32; // 32 ~ 127
	
	char* s = (char*)malloc(sizeof(char) * strlen(str) + 2); // free?
	memcpy(s, str, sizeof(char) * strlen(str));

	s[pos] = rand_char;
	
	for(int i=pos+1; i<strlen(str)+1; i++){
		s[i] = str[i-1];
	}

	return s;
}

char*
flip_random_character(char* str){
	if(str == NULL) return NULL;

	int pos;
	pos = rand()%strlen(str); // 0 ~ strlen(str)	
	
	char c = str[pos];	
	int bit; 
	bit = 1 << rand()%7;
	char new_c = c ^ bit;
//	printf("[DEBUG] Flip: %d in '%c' giving '%c'\n", bit, c, new_c);
	
	char* s = (char*)malloc(sizeof(char) * strlen(str) + 2); // free?
	memcpy(s, str, sizeof(char) * strlen(str));
	s[pos] = new_c;

	return s;
}

char*
mutate(char* str){
	int mutators = rand()%3+1;
	char* mutate;
	if(mutators == 1){
		mutate = delete_random_character(str);
	}
	else if(mutators == 2){
		mutate =insert_random_character(str);
	}
	else{
		mutate = flip_random_character(str);
	}

//	printf("%s\n", mutate);
	return mutate;
}
