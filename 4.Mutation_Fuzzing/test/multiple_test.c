#include "../include/http_program.h"
#include "../include/mutating.h"

#include <assert.h>

int main(){
	srand((unsigned int)time(NULL));
	
	char* seed_input = "http://www.google.com/search?q=fuzzing";
	char* inp = (char*)malloc(sizeof(char) * (strlen(seed_input) + 1));
	strncpy(inp, seed_input, strlen(seed_input));

	int valid = 0;
	int trial = 50;
	
	for(int i=0; i<trial; i++){
		strcpy(inp, mutate(inp, strlen(inp)));
		if(i%5 ==0) printf("[DEBUG] %d mutations: %s\n", i, inp);
		if(is_valid_url(inp) == 1){
			valid++;
		}
	}

	printf("[Valid] %f\n", (float)valid/20);

}
