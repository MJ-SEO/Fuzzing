#ifndef SCHED
#define SCHED

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#define DATA_MAX 4096

typedef struct seed{
	char data[DATA_MAX];   // file name
	size_t length;
	int energy;
} seed_t;



// assign energy in each seed  
int assign_energy(seed_t* seed, int n_input);

// get weigth of each seed
double* normalized_energy(seed_t* seed, int n_input, int* sum_energy);

// convert weighted seed list into index
int convert_energy_index(int sum_energy, double* norm_energy_list, int n_input);

// choose one seed with weight
char* choose_seed(seed_t* seed, int n_input);

#endif








