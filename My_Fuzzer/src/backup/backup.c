#include "../include/fuzzer.h"
#include "../include/create_input.h"

#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

static test_config_t fuzz_config; 
static int in_pipes[2] ;
static int out_pipes[2] ;
static int err_pipes[2] ;
static pid_t child_pid;
static int gcov_flag;
static int gcov_line;
static int gcov_line_for_ratio;
static int* bitmask;

typedef struct gcov_info{
	int line;
	int union_line; 
} gcov_t;

void
time_handler(int sig){
	if(sig == SIGALRM){
		perror("timeout ");
		kill(child_pid, SIGINT);
	}
}

void
make_tempdir(char* dir_name){
	char template[] = "tmp.XXXXXX";
	char* tempdir = mkdtemp(template);
	if(tempdir == NULL){
		perror("Mkdtemp Error\n");
		exit(1);
	}

	strcpy(dir_name, tempdir);
}

void
fuzzer_init(test_config_t * config, char* dir_name, int* flag){
	if(config->f_min_len < MINLEN || config->f_max_len > MAXLEN){
		perror("[fuzzer_init] - Fuzzer Length Error\n");
		exit(1);
	}
	if(config->f_min_len > config->f_max_len){
		perror("[fuzzer_init] - Fuzzer Length Error\n");
		exit(1);
	}
	if(config->f_char_start < 0 || config->f_char_start > 127){
		perror("[fuzzer_init] - Fuzzer Config Error\n");
		exit(1);
	}
	if(config->f_char_range < 0 || (config->f_char_start + config->f_char_range) > 255){
		perror("[fuzzer_init] - Fuzzer Range Error\n");
		exit(1);
	}
	if(strlen(config->binary_path) > MAXLEN){
		perror("[fuzzer_init] - Fuzzer Path Error\n");
		exit(1);
	}

	fuzz_config.f_min_len = config->f_min_len;
	fuzz_config.f_max_len = config->f_max_len;
	fuzz_config.f_char_start = config->f_char_start;
	fuzz_config.f_char_range = config->f_char_range;

	strcpy(fuzz_config.binary_path, config->binary_path);

	fuzz_config.trial = config->trial;

	fuzz_config.timeout = config->timeout;

	fuzz_config.oracle = config->oracle;
	
	if(config->source != 0x0){
		gcov_flag = 1;
		fuzz_config.source = config->source;
	}

	make_tempdir(dir_name);
}

void
execute_prog(test_config_t * config, char* input, int input_size, char* dir_name, int file_num){
	char* input_name = (char*)malloc(sizeof(char)*25);
	sprintf(input_name, "%s/input%d", dir_name, file_num);
	FILE* input_file = fopen(input_name, "wb");

	fwrite(input, 1, input_size, input_file);

	fclose(input_file);

	dup2(in_pipes[0], 0);
	close(in_pipes[0]);
	close(in_pipes[1]);

	close(out_pipes[0]);
	close(err_pipes[0]);

	dup2(out_pipes[1], 1);
	dup2(out_pipes[1], 2);


	execl(config->binary_path, config->binary_path, input, NULL);
	perror("[excute_prog] - Execution Error\n");
	exit(1);
}

int
get_info(test_config_t * config, char* input, int input_size, char* dir_name, int file_num){
	close(out_pipes[1]);
	close(err_pipes[1]);

	write(in_pipes[1], input, input_size);
	close(in_pipes[1]);

	int exit_code;
	wait(&exit_code);

	char buffer[1024];
	ssize_t s;

	char* output_name = (char*)malloc(sizeof(char)*15);
	sprintf(output_name, "%s/output%d", dir_name, file_num);
	FILE* output_file = fopen(output_name, "wb");

	while((s = read(out_pipes[0], buffer, 1024))> 0){
		if(fwrite(buffer, 1, s, output_file) != s){
			perror("Output File Make Error");
		}
	}

	char* err_name = (char*)malloc(sizeof(char)*15);
	sprintf(err_name, "%s/error%d", dir_name, file_num);
	FILE* err_file = fopen(err_name, "wb");

	while((s = read(err_pipes[0], buffer, 1024)) > 0){
		if(fwrite(buffer, 1, s, err_file) != s){
			perror("Error File Make Error");
		}
	}

	close(out_pipes[0]);
	close(err_pipes[0]);

	free(output_name);
	free(err_name);
	fclose(output_file);
	fclose(err_file);

	return exit_code;
}


void
run_gcov(char* source){
	pid_t gcov_child = fork();
	
	if(gcov_child == 0){
		execl("/usr/bin/gcov", "gcov", "-c", source, NULL);
		perror("run_gcov: Execution Error!");
		return;
	}
	else if(gcov_child > 0){
		int exit_code;
		wait(&exit_code);
		if(exit_code != 0){
			perror("GCOV Execute Error!");
			return;
		}
	}
	else{
		perror("run_gcov: Fork Error!");
		exit(1);
	}
}

int
run(test_config_t* config, char* input, int input_size, char* dir_name, int file_num){
	if (pipe(in_pipes) != 0 || pipe(out_pipes) != 0 || pipe(err_pipes) != 0) {
		perror("Pipe Error\n") ;
		exit(1) ;
	}

	int return_code;

	alarm(config->timeout);

	child_pid = fork();
	if (child_pid == 0) {
		execute_prog(config, input, input_size, dir_name, file_num) ;
	}
	else if (child_pid > 0) {
		return_code = get_info(config, input, input_size, dir_name, file_num) ;
	}
	else {
		perror("Fork Error\n") ;
		exit(1) ;
	}

	return return_code;
}

int 
get_gcov_line(char* c_file){
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
			if(flag == 0 && ((atoi(ptr) > 0)) || strstr(ptr, "#") != NULL) gcov_line_for_ratio++;		
			if(flag == 0) n_line++;		
			ptr = strtok(NULL, ":");
			flag++;
		}
	}
	fclose(fp);
	return n_line;
}

int
union_bits(int* dest, int* src){
	int bitsum = 0;
	for(int i=0; i<gcov_line; i++){
		if(dest[i] == 1 || src[i] == 1){
			dest[i] = 1;
			bitsum++;	
		}
	}
	return bitsum;
}

void
read_gcov_coverage(char* c_file, gcov_t* curr_info, int idx){
	char gcov_file[64];
	strcpy(gcov_file, c_file);
	strcat(gcov_file, ".gcov");

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

	int* curr_mask = (int*)malloc(sizeof(int) * gcov_line);
	//memset(curr_mask, 0, sizeof(gcov_line));
	for(int i=0; i<gcov_line; i++){
		curr_mask[i] = 0;
	}

	while((ret = getline(&line, &size, fp)) != -1){
		char* ptr = strtok(line, ":");
		int flag = 0;
		while(ptr != NULL){
			if(flag == 0 && atoi(ptr) > 0){
				curr_mask[n_bit] = 1;
				n_line++;			
			}
			ptr = strtok(NULL, ":");
			flag++;
		}
		n_bit++;
	}
	
	curr_info[idx].line = n_line;
	curr_info[idx].union_line = union_bits(bitmask, curr_mask);

	fclose(fp);
}

void 
show_result(int* return_code, int* prog_results, int trial){
	for(int i=1; i<=trial; i++){
		printf("[%d] Return code: %d, Result: %d\n", i, return_code[i], prog_results[i]);
	}	
}

void
show_stat(int* return_code, int trial){
	int no_backslash_d_failures = 0;
	int no_8bit_failures = 0;
	int no_dot_failures = 0;
	int normal_case = 0;

	for(int i=0; i<trial; i++){
		if(return_code[i] == 256) no_dot_failures++;
		else if(return_code[i] == 512) no_8bit_failures++;
		else if(return_code[i] == 768) no_backslash_d_failures++;
		else normal_case++;	
	}

	printf("==========Fuzzer Summary===========\n");
	printf("Number of Tests: %d\n", trial);
	printf("No_dat_Failures: %d\n", no_dot_failures);
	printf("No_8bit_Failures: %d\n", no_8bit_failures);
	printf("No_backslash_d_Failures: %d\n", no_backslash_d_failures);
	printf("Normal cases: %d\n", normal_case);
	printf("===================================\n");
}

void
show_gcov(int* return_code, gcov_t* gcov_result, int trial){
	printf("=============Fuzzer Summary==============\n");
	for(int i=1; i<=trial; i++){
		printf("[Try %d] Line: %d Union: %d Latio:%lf\n", i, gcov_result[i].line, gcov_result[i].union_line, (double)gcov_result[i].union_line/gcov_line_for_ratio);
	}
	printf("=========================================\n");
}

void
fuzzer_main(test_config_t* config){
	srand((unsigned int)time(NULL));
	
	signal(SIGALRM, time_handler);

	char dir_name[20];

	fuzzer_init(config, dir_name, &gcov_flag);	
	
	int* prog_results = (int*)malloc(sizeof(int) * (fuzz_config.trial + 1));
	int* return_code = (int*)malloc(sizeof(int) * (fuzz_config.trial + 1));
	gcov_t* gcov_results= (gcov_t*)malloc(sizeof(gcov_t) * (fuzz_config.trial + 1));

	for(int i = 1; i <= fuzz_config.trial; i++){
		char* input = (char*)malloc(sizeof(char)*(fuzz_config.f_max_len + 1)); 
		
		int fuzz_len = create_input(&fuzz_config, input);

		return_code[i] = run(&fuzz_config, input, fuzz_len, dir_name, i);
		free(input);

		if(gcov_flag == 1){
		       	run_gcov(fuzz_config.source);
			if(i==1) {
				gcov_line = get_gcov_line(fuzz_config.source);
				bitmask = (int*)malloc(sizeof(int) * gcov_line);
				memset(bitmask, 0, sizeof(int)*gcov_line);
			}
			read_gcov_coverage(fuzz_config.source, gcov_results, i);
			if(remove("cgi_decoder.gcda") != 0){
				perror("GCDA deletes FAILED");
			}
		}	

		fuzz_config.oracle(dir_name, i, prog_results, return_code[i]);
	}

	//show_result(return_code, prog_results, fuzz_config.trial);
	//show_stat(return_code, fuzz_config.trial);
	show_gcov(return_code, gcov_results, fuzz_config.trial);
	free(prog_results);
	free(return_code);
	free(gcov_results);
}
