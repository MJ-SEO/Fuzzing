#include "../include/sched.h"

//#define DEBUG

/*
int
seed(char* src, char* dst){	// Receive f_name in src Return seed to dst, Return int is length of seed
	
}
*/

int test[3];

int 
assign_energy(seed_t* seed, int n_input){
	for(int i=0; i<n_input; i++){
		seed[i].energy = 3;
	}
	
	return 1;
}

int*
normalized_energy(seed_t* seed, int n_input, int* sum_energy){
	int* energy_list = (int*)malloc(sizeof(int) * n_input);
	int* norm_energy_list = (int*)malloc(sizeof(int) * n_input);
	
	for(int i=0; i<n_input; i++){
		energy_list[i] = seed[i].energy;
		*sum_energy += energy_list[i];
	}
	
	norm_energy_list[0] = energy_list[0];

	for(int i=1; i<n_input; i++){
		norm_energy_list[i] = energy_list[i] + norm_energy_list[i-1];
	}

	return norm_energy_list;
}

int
convert_energy_index(int sum_energy, int* n_energy_list, int n_input){
	int randnum = rand()%sum_energy;
	
	for(int i=0; i<n_input; i++){
		if(i==0){
			for(int j=0; j<n_energy_list[i]; j++){
				if(randnum == j) return i;
			}
		}
		else{
			for(int j=n_energy_list[i-1]; j<n_energy_list[i]; j++){
				if(randnum == j) return i;
			}
		}
	}

	return -1;
}

char*
choose_seed(seed_t* seed, int n_input){
	assign_energy(seed, n_input);
	int sum_energy = 0;
	int* norm_energy_list;
	
	norm_energy_list = normalized_energy(seed, n_input, &sum_energy);

#ifdef DEBUG
	printf("[DEBUG] sum_E: %d\n", sum_energy);
	for(int i=0; i<n_input; i++){
		printf("[DEBUG] norm[%d]: %d\n", i, norm_energy_list[i]);
	}
#endif

	int index;
   	if((index = convert_energy_index(sum_energy, norm_energy_list, n_input)) == -1){
		perror("convert error\n");
		exit(1);
	}
	test[index]++;

	free(norm_energy_list);
	return seed[index].data;
}

/*
int main(){	 // TEST DRIVER for scheduler
	srand((unsigned int)time(NULL));
	DIR* inp_dir;
	struct dirent* dp = NULL;
	int n_input = 0;

	seed_t* seed = (seed_t*)malloc(sizeof(seed_t) * 100);	// MEMORY?
	
	if((inp_dir = opendir("input")) == NULL){
		printf("DIR open error");
		exit(1);
	}	

	while((dp = readdir(inp_dir)) != NULL){
		if(dp->d_type == 8){
			printf("[FILE]%s\n", dp->d_name);
			strcpy(seed[n_input].data, dp->d_name);		
			n_input++;
		}
	}
	
	for(int i=0; i<10000; i++){
		char* chosen = choose_seed(seed, n_input);	
	}

	for(int i=0; i<3; i++){
		printf("%d ", test[i]);
	}
	printf("\n");


} */
