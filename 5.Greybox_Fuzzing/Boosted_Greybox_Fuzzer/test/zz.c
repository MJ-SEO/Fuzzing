#include <stdio.h>

int main(void) {
	int height[10], weight[10]; // Height (cm), weight (kg) of 10 people
	float bmi[10]; // Obesity figures for 10 people
	int count=0; // number of obese people
	int i; // variable for loop

	int n =10;

	for(i=0; i<n; i++){
		printf("Person %d: height and weight? ", i+1);
		scanf("%d %d",&height[i], &weight[i]);

		printf("up; %d\n", weight[i]);
		printf("down: %f\n", height[i] * height[i] * 0.0001);
		
		float temp =  height[i] * height[i] * 0.0001;
		printf("temp: %f\n", temp);

	      	bmi[i] = (float)(weight[i] / (height[i]*height[i]*0.0001));
		
		printf("[DEBUG] bmi: %f\n", bmi[i]);
	}
	printf("\n\n");

	for (i=0; i<n; i++){
		if (bmi[i] >=25){
			printf("Person %d is obese.\n",i+1);
			count++;
		}
		else continue;
	}
	printf("In total, %d people are obese.",count);
	return 0;
}
