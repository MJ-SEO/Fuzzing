#ifndef COVERAGE
#define COVERAGE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sched.h"

typedef struct gcov_sources{	// source specific gcov info
	char* bitmap;
	char* branch_bitmap;
	int gcov_line;
//	int gcov_line_for_ratio;
//	int gcov_line_for_branch;

	int tot_lines;
	int tot_branches;

	char hash_table[65546];
} gcov_src_t;  

typedef struct gcov_info{	// Trial specific gcov info
	int line;
	int branch_line;
	
	int union_line;
	int branch_union_line;
} gcov_t;

int get_gcov_line(char* c_file, int* line, int* branch);

int union_bits(char* dest, char* src, int lines);

int read_gcov_coverage(char* c_file, gcov_t** curr_infor, int trial, int n_src, gcov_src_t* gcov_info, seed_t* seed);

void gcda_remove(char* c_file, char* path);

#endif
