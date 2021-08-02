#include <stdio.h>
#include <stdlib.h>

double my_sqrt(int x){
	double apporx = 0;
	double guess = x/2;

	while(apporx != guess){
		printf("[DEBUG] apporx = %lf\n", apporx);
		apporx = guess;
		guess = (apporx + x / apporx) / 2;
	}

	return apporx;
}

void sqrt_program(char* arg){
	int x = atoi(arg);
	if(x <= 0){
		printf("Illegal Input\n");
	}
	else{	
		printf("The root of %d is %lf\n", x, my_sqrt(x));
	}
}

int main(){
	while(1){
		char* input = (char*)malloc(sizeof(char)*1000);
		scanf("%s", input);
		sqrt_program(input);
		free(input);
	}

	return 0;
}
