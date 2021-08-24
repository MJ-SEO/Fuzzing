#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/http_program.h"
#include "../include/mutating.h"

int
is_valid_url(char* target_url){
	if(http_program(target_url) == 0) return 1;
	else return 0;
}

int main(){
	char* url = "http://www.google.com/search?q=fuzzing";

	assert(is_valid_url(url) == 1);
	assert(is_valid_url("xyzzy") == 0);
	
	char* seed_input = "http://www.google.com/search?q=fuzzing";
	int valid = 0;
	for(int i=0; i<20; i++){
		char* input = mutate(seed_input);
		if(is_valid_url(input) == 1){
			valid++;
		}
	}

	printf("[Valid] %f\n", (float)valid/20);
}
