#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

char*
fuzzer(int max_length, int start, int range){
	int strlen = (rand()%max_length+1)+1;
	char* out = (char*)malloc(sizeof(char) * strlen);
	for(int i=0; i<strlen; i++){
		out[i] = (char)((rand()%range) + (start+range));
	}
	return out;
}


int main(){
	srand((unsigned int)time(NULL));

	char* basename = "input.txt";
	
	char template[] = "tmp.XXXXXX";
	char *tempdir = mkdtemp(template);
	
	char* path = (char*)malloc(sizeof(char) * 50);
	strcpy(path, tempdir);
	strcat(path, "/");
	strcat(path, basename);

	for(int i=0; i<100; i++){
		char* data = fuzzer(100, 32, 32);
		FILE *fp;
		fp = fopen(path, "w+");
		if(fp == NULL){
			fputs("File Error\n", stderr);
			exit(1);
		}
		fprintf(fp, "%s", data);

		char* commend = (char*)malloc(sizeof(char) * 100);
		sprintf(commend, "cat %s | bc ", path);

		fclose(fp);

		char buf[128];
		FILE *res = popen(commend, "r");
		if(res == NULL){
			fputs("FILLE Error\n", stderr);
			exit(1);
		}
		
		fscanf(res, "%s", buf);
		printf("%s : %s\n", path, buf);

	}
	return 0;
}
