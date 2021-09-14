#ifndef COVERAGE
#define COVERAGE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct gcov_sources{	// source specific gcov info
	int* bitmap;
	int* branch_bitmap;
	int gcov_line;
	int gcov_line_for_ratio;
	int gcov_line_for_branch;
} gcov_src_t;  

typedef struct gcov_info{	// Trial specific gcov info
	int line;
	int branch_line;
	
	int union_line;
	int branch_union_line;
} gcov_t;

int get_gcov_line(char* c_file, int* line, int* branch);

int union_bits(int* dest, int* src, int lines);

void read_gcov_coverage(char* c_file, gcov_t** curr_infor, int trial, int n_src, int lines, int* bitmap, int* branch_bitmap, int* new_mutate);

void gcda_remove(char* c_file, char* path);

#endif
