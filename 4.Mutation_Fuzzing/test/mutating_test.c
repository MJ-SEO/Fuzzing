#include "../include/mutating.h"

int main(){
	srand((unsigned int)time(NULL));
	
	char* seed = "A quick brown fox";

	for(int i=0; i<10; i++){
		printf("%s\n", mutate(seed));
	}
}
