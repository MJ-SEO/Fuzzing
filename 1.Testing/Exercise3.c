#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

double my_sqrt_fixed(int x){
	assert(0 <= x);
	if(x == 0){
		return 0;
	}
	return my_sqrt(x);
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

void quadratic_solver(int a, int b, int c){
	int q = b * b - 4 * a * c;
	double solution1 = (-b + my_sqrt_fixed(q)) / (2*a);
	double solution2 = (-b - my_sqrt_fixed(q)) / (2*a);
	printf("%lf %lf\n", solution1, solution2);
}


double* 
fixed_quadratic_solver(int a, int b, int c){
	double *answer = (double*)malloc(sizeof(double)*2);
	if(a==0){
		if(b==0){
			if(c==0){
				answer[0] = 0;
				answer[1] = 0x0;
				return answer;
			}
			else{
				answer[0] = 0x0;
				answer[1] = 0x0;
				return answer;
			}
		}
		else{
			answer[0] = -c/b;
			answer[1] = 0x0;
			return answer;
		}
	}

	int q = b * b - 4 * a * c;
	if(q < 0){
		answer[0] = 0x0;
		answer[1] = 0x0;
		return answer;
	}
	if(q==0){
		answer[0] = -b/2 * a;
		answer[1] = 0x0;
		return answer;
	}

	double answer[0] = (-b + my_sqrt_fixed(q)) / (2*a);
	double answer[1] = (-b - my_sqrt_fixed(q)) / (2*a);
	
	return answer;
}

int main(){
	quadratic_solver(3, 4, 1);

	// part 1
	
	quadratic_solver(0, 2, 1); // divide by 0
	quadratic_solver(3, 2, 1); // violate my_sqrt_fixed() q has to more than 0
	
	// part 2
	
	double *zz;
	zz =fixed_quadratic_solver(3, 4, 1);
	
	
	// part 3

	return 0;
}
