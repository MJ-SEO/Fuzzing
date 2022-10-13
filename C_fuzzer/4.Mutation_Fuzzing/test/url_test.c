#include "../include/http_program.h"
#include "../include/mutating.h"

#include <assert.h>

int main(){
	srand((unsigned int)time(NULL));
/*
	char* url = "http://www.google.com/search?q=fuzzing";

	assert(is_valid_url(url) == 1);
	assert(is_valid_url("xyzzy") != 0);
*/
	
	char* seed_input; // = "http://www.google.com/search?q=fuzzing";
	scanf("%s", seed_input);

	int valid = 0;
	int trial = 20;
	for(int i=0; i<trial; i++){
		char* input = mutate(seed_input, strlen(seed_input));
		printf("[DEBUG] input: %s\n", input);
		if(is_valid_url(input) == 1){
			valid++;
		}
	}

	printf("[Valid] %f\n", (float)valid/20);

}
