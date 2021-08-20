#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct coverage{
	char c_file[64];
	int line_number;
} coverage_t;

void
read_gcov_coverage(char* c_file){
	char gcov_file[64];
	strcpy(gcov_file, c_file);
	strcat(gcov_file, ".gcov");

	FILE* fp;
	fp = fopen(gcov_file, "rb");
	if(fp == NULL){
		perror("File Open Error!");
		exit(1);
	}

	ssize_t ret;
	char* line = NULL;
	size_t size = 0;
	char* delim = ":";

	coverage_t* cov_list = (coverage_t*)malloc(sizeof(coverage_t) * 100); // Linked list?
	int index = 0;

	while((ret = getline(&line, &size, fp))!= -1){
		char * ptr = strtok(line, delim);
		int flag = 0;
		while(ptr != NULL){
			if(flag == 0 && atoi(ptr) == 0) break;

			if(flag == 1){
				strcpy(cov_list[index].c_file, c_file);
				cov_list[index].line_number = atoi(ptr);
				index++;		
			}

			ptr = strtok(NULL, delim);
			flag++;
		}
	}

	for(int i=0; i<index; i++){
		printf("[%s, %d]\n", cov_list[i].c_file, cov_list[i].line_number);
	}

	fclose(fp);
}

