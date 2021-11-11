#include <stdio.h>

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

int main(){
	int input = 0;
	while(1){
		scanf("%d", &input);
		if(input == -2) break;
		printf("result: %lf\n", my_sqrt(input)); 
	}

	return 0;
}
