#include "../include/fuzzer.h"
#include <dirent.h>
#include <sys/types.h>

int 
oracle(char* dir_name, int file_num, int* result, int return_code){
	char input_file[25];
	sprintf(input_file, "%s/input%d", dir_name, file_num);    
	
	char output_file[25];
	sprintf(output_file, "%s/output%d", dir_name, file_num);    

	char err_file[25]; 
	sprintf(err_file, "%s/error%d", dir_name, file_num);   

	FILE* fp = fopen(err_file, "rb");
	if(fp == NULL){
		perror("Error file Open Failed\n");
		result[file_num] = 2;
		return 1;
	}

	char buffer[1024];
	size_t s;

	if((s = fread(buffer, 1, sizeof(buffer), fp)) > 0){
		result[file_num] = 2;
		return 0;	
	}
	else{
		fclose(fp);
		char a, b;
		FILE* input_fp = fopen(input_file, "rb");
		FILE* output_fp = fopen(output_file, "rb");
		if(input_fp == NULL || output_fp == NULL){
			perror("INPUT/OUTPUT file Open Failed\n");
			result[file_num] = 2;
			return 1;
		}
		while(1){
			if(feof(input_fp) == 0 && feof(output_fp) == 0){
				a = fgetc(input_fp);
				b = fgetc(output_fp);
				if(a!=b){
					result[file_num] = 1;
					break;
				}
			}
			else if(feof(input_fp) != 0 && feof(output_fp) == 0){
				result[file_num] = 1;
				break;
			}
			else if(feof(input_fp) == 0 && feof(output_fp) != 0){
				result[file_num] = 1;
				break;
			}
			else{
				result[file_num] = 0;
				break;
			}
		}

		fclose(input_fp);
		fclose(output_fp);
	}
	return 0;
}

void
config_setting(test_config_t* config){
	config->f_min_len = 5;
	config->f_max_len = 30;
	
	config->f_char_start = 32;
	config->f_char_start = 24;

	char* options[4] = {"-b"};
	config->cmd_args = options;
	config->option_num = 1;

	strcpy(config->binary_path, "/bin/cat");

	config->oracle = oracle;
}

int main(){
	test_config_t config;

	config_init(&config);

	config_setting(&config);

	fuzzer_main(&config);
}
