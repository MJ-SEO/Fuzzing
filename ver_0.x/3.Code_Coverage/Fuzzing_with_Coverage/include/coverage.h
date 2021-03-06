#ifndef COVERAGE
#define COVERAGE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int* bitmap;
int* branch_bitmap;
int gcov_line;
int gcov_line_for_ratio;
int gcov_line_for_branch;

typedef struct gcov_info{
	int line;
	int union_line;
	int branch_line;
	int branch_union_line;
} gcov_t;

int get_gcov_line(char* c_file);

int union_bits(int* dest, int* src);

void read_gcov_coverage(char* c_file, gcov_t* curr_infor, int idx);

void gcda_remove(char* c_file);

#endif
