#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define EPSILON 1e-8

double my_sqrt(int x){
	double apporx = 0;
	double guess = x/2;
	while(apporx != guess){
		apporx = guess;
		guess = (apporx + x / apporx) / 2;
	}
	return apporx;
}

void assertEquals(double approx ,int expect){
	assert((abs(approx - expect)) < EPSILON);
}

int main(){
	srand((unsigned int)time(NULL));

	assertEquals(my_sqrt(4), 2);
	assertEquals(my_sqrt(9), 3);
	assertEquals(my_sqrt(100), 10);

	assertEquals(my_sqrt(2) * my_sqrt(2), 2);
	assertEquals(my_sqrt(3) * my_sqrt(3), 3);
	assertEquals(my_sqrt(42.11) * my_sqrt(42.11), 42.11);
	
	for(int i=2; i<1000; i++){
		assertEquals(my_sqrt(i) * my_sqrt(i), i);
	}

	clock_t start = clock();
	for(int i=2; i<10000; i++){
		int x = (rand()%100000)+1;
		assertEquals(my_sqrt(x) * my_sqrt(x), x);
	}
	clock_t end = clock();

	printf("mile second %lf\n", (double)(end-start)/CLOCKS_PER_SEC * 1000);

	return 0;
}
