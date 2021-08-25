#include "../include/coverage.h"

int 
get_gcov_line(char* c_file, int* gcov_line_for_ratio, int* gcov_line_for_branch){
	char gcov_file[64];
	strcpy(gcov_file, c_file);
	strcat(gcov_file, ".gcov");

	FILE* fp;
	fp = fopen(gcov_file, "rb");
	if(fp == NULL){
		perror("get_gcov: File Opne Error!");
		exit(1);
	}

	ssize_t ret;
	char* line = NULL;
	size_t size = 0;
	int n_line = 0;
	
	while((ret = getline(&line, &size, fp)) != -1){
		char* ptr = strtok(line, ":");
		int flag = 0;
		while(ptr != NULL){
			if((flag == 0 && atoi(ptr) > 0 ) || (flag == 0 && strstr(ptr, "#") != NULL)){
			       	*gcov_line_for_ratio = (*gcov_line_for_ratio) + 1;		
			}
			if(flag == 0 && strstr(ptr, "branch") != NULL) *gcov_line_for_branch = (*gcov_line_for_branch) + 1;
			if(flag == 0) n_line++;		
			ptr = strtok(NULL, ":");
			flag++;
		}
	}
	fclose(fp);
	return n_line;
}

int
union_bits(int* dest, int* src, int lines){
	int bitsum = 0;
	for(int i=0; i<lines; i++){
		if(dest[i] == 1 || src[i] == 1){
			dest[i] = 1;
			bitsum++;	
		}
	}
	return bitsum;
}

void
read_gcov_coverage(char* c_file, gcov_t* curr_info, int idx, int lines, int* bitmap, int* branch_bitmap){
	char gcov_file[64];
	strcpy(gcov_file, c_file);
	strcat(gcov_file, ".gcov");

//	printf("[DEBUG] read_gcov_coverage, gcov_file: %s\n", gcov_file);

	FILE* fp;
	fp = fopen(gcov_file, "rb");
	if(fp == NULL){
		perror("read_gcov: File Opne Error!");
		exit(1);
	}

	ssize_t ret;
	char* line = NULL;
	size_t size = 0;
	int n_bit = 0;
	int n_line = 0;
	int n_branch = 0;

//printf("[DEBUG] read_gcov_coverage, lines: %d\n", lines);
	int* curr_mask = (int*)malloc(sizeof(int) * lines);
	memset(curr_mask, 0, sizeof(int) * lines);
	
	int* branch_mask = (int*)malloc(sizeof(int) * lines);
	memset(branch_mask, 0, sizeof(int) * lines);

	while((ret = getline(&line, &size, fp)) != -1){
		char* ptr = strtok(line, ":");
		int flag = 0;
		while(ptr != NULL){
			if(flag == 0 && atoi(ptr) > 0){
				curr_mask[n_bit] = 1;
				n_line++;			
			}
			if(flag == 0 && strstr(ptr, "taken") != NULL){
				branch_mask[n_bit] = 1;
				n_branch++;	
			}
			ptr = strtok(NULL, ":");
			flag++;
		}
		n_bit++;
	}
	
	curr_info[idx].line = n_line;
	curr_info[idx].union_line = union_bits(bitmap, curr_mask, lines);

	curr_info[idx].branch_line = n_branch;
	curr_info[idx].branch_union_line = union_bits(branch_bitmap, branch_mask, lines);

	free(curr_mask);
	free(branch_mask);	
	fclose(fp);
}

void
gcda_remove(char* c_file){
	char* gcda_file = (char*)malloc(sizeof(char) * strlen(c_file) + 4);
	
	strncpy(gcda_file, c_file, strlen(c_file) - 2);
	strcat(gcda_file, ".gcda");
	
	if(remove(gcda_file) != 0){
		perror("GCDA delete failed");
	}

	free(gcda_file);
}
