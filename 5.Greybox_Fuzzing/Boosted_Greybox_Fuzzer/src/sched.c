#include "../include/sched.h"

// #define DEBUG

int 
assign_energy(seed_t* seed, int n_input, double exponent){
	for(int i=0; i<n_input; i++){
#ifdef DEBUG
		printf("[ASSIGNT] seed[%d] %d, %lf\n", i, seed[i].num_executed, exponent);
#endif

		seed[i].energy = 1 / (pow(seed[i].num_executed, exponent));
//		seed[i].energy = INITAL_E / (pow(seed[i].num_executed, exponent));
#ifdef DEBUG
		printf("[ASSIGNT] seed[%d] energy: %Lf\n", i, seed[i].energy);
#endif

	}
	return 1;
}


double*
normalized_energy(seed_t* seed, int n_input, double* sum_energy){
	double* energy_list = (double*)malloc(sizeof(double) * n_input);
	double* norm_energy_list = (double*)malloc(sizeof(double) * n_input);
	
	for(int i=0; i<n_input; i++){
		energy_list[i] = seed[i].energy;
		*sum_energy += energy_list[i];
	}
	
	for(int i=0; i<n_input; i++){
		norm_energy_list[i] = energy_list[i]/(*sum_energy);
	}

	return norm_energy_list;
}

int
convert_energy_index(double sum_energy, double* n_energy_list, int n_input){
	double randnum = (double)rand()/INT_MAX; // 0 ~ 1
	double percentage = randnum * 100.0f; // 0 ~ 100%

	double accumlate = 0;
	for(int i=0; i< n_input; i++){
		accumlate += n_energy_list[i] * 100.0f;
		if(percentage < accumlate){
			return i;
		}
	}
/*
	double cumulate[n_input];
	
	cumulate[0] = n_energy_list[0] * 100.0f;
	for(int i=1; i<n_input; i++){
		cumulate[i] = cumulate[i-1] + n_energy_list[i] * 100.0f;
	}

	for(int i=0; i<n_input; i++){
		if(i==0){
			if(percentage <= cumulate[i]) return i;
		}
		else{
			if(percentage > cumulate[i-1] && percentage <= cumulate[i]) return i;
		}
	}
*/
	return -1;
}

char*
choose_seed(seed_t* seed, int n_input, double exponent, int* choosed, int greybox){
	assign_energy(seed, n_input, exponent);

	double sum_energy = 0;
	double* norm_energy_list;
	
	norm_energy_list = normalized_energy(seed, n_input, &sum_energy);

#ifdef DEBUG
	printf("[CHOOSE] sum_energy: %lf\n", sum_energy);
	for(int i=0; i<n_input; i++){
		printf("[CHOOSE] norm[%d]: %lf\n", i, norm_energy_list[i]);
	}
#endif

	int index;
	if((index = convert_energy_index(sum_energy, norm_energy_list, n_input)) == -1){
		perror("choose_seed: convert error\n");
		exit(1);
	}

	if(greybox == 1){
		seed[index].num_executed++;
	}

	*choosed = index;

//	printf("[DEBUG] seed[%d] executed %d\n", index, seed[index].num_executed);
	
	return seed[index].data;
}


/*
int main(){	 // TEST DRIVER for scheduler
	srand((unsigned int)time(NULL));
	DIR* inp_dir;
	struct dirent* dp = NULL;
	int n_input = 0;
	int choosed = 0;

	seed_t* seed = (seed_t*)malloc(sizeof(seed_t) * 100);	// MEMORY?
	
	if((inp_dir = opendir("../../Test/input")) == NULL){
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

	for(int i=0; i<10; i++){
		char* chosen = choose_seed(seed, n_input, 0.5, &choosed);	
	}

	for(int i=0; i<3; i++){
		printf("%d ", test[i]);
	}
	printf("\n");

}*/
