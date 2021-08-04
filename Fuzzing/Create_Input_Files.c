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
	char* buffer;
	char* basename = "input.txt";
	char* data = fuzzer(100, 32, 32);

	char template[] = "tmp.XXXXXX";	
	char* tempdir = mkdtemp(template);
	
	char* path = (char*)malloc(sizeof(char) * 50);
	strcpy(path, tempdir);
	strcat(path, "/");
	strcat(path, basename);

	FILE *fp;
	fp = fopen(path, "w+");
	if(fp == NULL){
		fputs("File Error\n", stderr);
		exit(1);
	}
	fprintf(fp, "%s", data);
	
	char* contents = (char*)malloc(sizeof(char)*200);
	
	fseek(fp, 0, SEEK_SET);
	fread(contents, 100, 1, fp);
	
	printf("D: %s\n", data);
	printf("C: %s\n", contents);
		
	assert(strcmp(contents, data) == 0);

	fclose(fp);
	free(path);
	return 0;
}
