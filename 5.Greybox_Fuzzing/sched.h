#ifndef SCHED
#define SCHED

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

typedef struct seed{
	char data[1024];   // file name
	int energy;
} seed_t;

// assign energy in each seed  
int assign_energy(seed_t* seed, int n_input);

// get weigth of each seed
int* normalized_energy(seed_t* seed, int n_input, int* sum_energy);

// convert weighted seed list into index
int convert_energy_index(int sum_energy, int* norm_energy_list, int n_input);

// choose one seed with weight
char* choose_seed(seed_t* seed, int n_input);

#endif








