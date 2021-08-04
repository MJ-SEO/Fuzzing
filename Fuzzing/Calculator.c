#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

int main(){
	FILE *fp;
	fp = fopen("target", "w+");
	if(fp == NULL){
		fputs("File Error\n", stderr);
		exit(1);
	}
	char* equation = (char*)malloc(sizeof(char)*200);
	scanf("%[^\n]s", equation);	
	strcat(equation, "\n");

	fprintf(fp, "%s", equation);
	
	printf("Equation: %s", equation);
	
	fclose(fp);	

	char buf[128];
	
	FILE *res = popen("bc target", "r");
	if(res == NULL){
		fputs("File Error\n", stderr);
		exit(1);
	}
	fscanf(res, "%s", buf);

	printf("Answer:%s\n", buf);

	return 0;
}
