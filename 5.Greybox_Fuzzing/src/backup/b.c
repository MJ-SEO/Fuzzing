#include "../include/fuzzer.h"
#include "../include/create_input.h"
#include "../include/coverage.h"

#define DEBUG

#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>

static test_config_t fuzz_config;	
static int in_pipes[2] ;	
static int out_pipes[2] ;
static int err_pipes[2] ;
static pid_t child_pid;
static char input_files[100][4096];

static int gcov_flag;
static int** bitmap;
static int** branch_bitmap;
static int* gcov_line;
static int* gcov_line_for_ratio;
static int* gcov_line_for_branch;

//static int* bitmap;
//static int* branch_bitmap;
//static int gcov_line;
//static int gcov_line_for_ratio;
//static int gcov_line_for_branch;


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
	if(config->mutation == 1){	// Mutation
		DIR* inp_dir;
		struct dirent* dp = NULL;
		int n_inputs = 0;

		if((inp_dir = opendir(config->mutation_dir)) == NULL){
			perror("[fuzzer_init] Target dir open failed");
			exit(1);
		}

		fuzz_config.mutation_dir = config->mutation_dir;

		while((dp = readdir(inp_dir)) != NULL){
			if(dp->d_type == 8){
				//	printf("[FILE] %s\n", dp->d_name);
				sprintf(input_files[n_inputs], "%s/%s", config->mutation_dir, dp->d_name); // TODO linked_list?
				//	printf("[REal] %s[%d]\n", input_files[n_inputs], n_inputs);
				n_inputs++;
			}		
		}

		fuzz_config.mutation = n_inputs;
	}

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
	fuzz_config.number_of_source = config->number_of_source;
	fuzz_config.source_path = config->source_path;
	fuzz_config.curr_dir = config->curr_dir;

	if(config->cmd_args != NULL) {
		if(config->number_of_source > 0){
			fuzz_config.cmd_args = (char **)malloc(sizeof(char *) * (config->option_num + 3)) ; 
			fuzz_config.cmd_args[0] = (char *)malloc(sizeof(char) * (strlen(config->binary_path) + 1)) ;
			strcpy(fuzz_config.cmd_args[0], config->binary_path);

			for(int i = 0 ; i < config->option_num; i++) {
				int length = strlen(config->cmd_args[i]) + 1; 
				fuzz_config.cmd_args[i+1] = (char *)malloc(sizeof(char) * length) ; 
				strcpy(fuzz_config.cmd_args[i+1], config->cmd_args[i]) ;
			}
			fuzz_config.cmd_args[config->option_num + 2] = NULL; 

		}
		else{
			fuzz_config.cmd_args = (char **)malloc(sizeof(char *) * (config->option_num + 2)) ; 
			fuzz_config.cmd_args[0] = (char *)malloc(sizeof(char) * (strlen(config->binary_path) + 1)) ;
			strcpy(fuzz_config.cmd_args[0], config->binary_path);

			for(int i = 0 ; i < config->option_num; i++) {
				int length = strlen(config->cmd_args[i]) + 1; 
				fuzz_config.cmd_args[i+1] = (char *)malloc(sizeof(char) * length) ; 
				strcpy(fuzz_config.cmd_args[i+1], config->cmd_args[i]) ;
			}
			fuzz_config.cmd_args[config->option_num + 1] = NULL; 
		}
	}
	else{
		if(config->number_of_source > 0){
			fuzz_config.cmd_args = (char **)malloc(sizeof(char *) * 3); 
			fuzz_config.cmd_args[0] = (char *)malloc(sizeof(char) * (strlen(config->binary_path) + 1)); 
			strcpy(fuzz_config.cmd_args[0], config->binary_path); 
			fuzz_config.cmd_args[2] = NULL; 

		}
		else{
			fuzz_config.cmd_args = (char **)malloc(sizeof(char *) * 2); 
			fuzz_config.cmd_args[0] = (char *)malloc(sizeof(char) * (strlen(config->binary_path) + 1)); 
			strcpy(fuzz_config.cmd_args[0], config->binary_path); 
			fuzz_config.cmd_args[1] = NULL; 
		}
	}

	fuzz_config.need_args = config->need_args;

	fuzz_config.timeout = config->timeout;

	fuzz_config.oracle = config->oracle;

	if(config->number_of_source > 0){
		for(int i=0; i<config->number_of_source; i++){
			char* s_path = (char*)malloc(sizeof(char) * 1024);
			sprintf(s_path, "%s%s", config->source_path, config->sources[i]);
			assert(access(s_path, F_OK) == 0 && "Target Source Not Exiset!");	
			free(s_path);
		}
		gcov_flag = 1;
		fuzz_config.sources = config->sources;
	}

	make_tempdir(dir_name);
}

void
execute_prog(test_config_t * config, char* input, int input_size, char* dir_name, int file_num){
	char* input_name = (char*)malloc(sizeof(char)*25);
	sprintf(input_name, "%s/input%d", dir_name, file_num);
	FILE* input_file = fopen(input_name, "wb");
	
	if(input_files == NULL){
		perror("execute_prog: Input-file error");
		exit(1);
	}

	fwrite(input, 1, input_size, input_file);

	fclose(input_file);

	dup2(in_pipes[0], 0);
	close(in_pipes[0]);
	close(in_pipes[1]);

	close(out_pipes[0]);
	close(err_pipes[0]);

	dup2(out_pipes[1], 1);	
	dup2(err_pipes[1], 2);
	
	if(config->need_args == 1){
		execv(config->binary_path, config->cmd_args);
	}
	else{
		execl(config->binary_path, config->binary_path, NULL);
	}

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

#ifdef DEBUG
	printf("[Get_info] input(%d): %s\n", input_size, input);
#endif

	char* output_name = (char*)malloc(sizeof(char)*15);
	sprintf(output_name, "%s/output%d", dir_name, file_num);
	FILE* output_file = fopen(output_name, "wb");

	if(output_file == NULL){
		perror("get_info: Output-file error");
		exit(1);
	}

	while((s = read(out_pipes[0], buffer, 1024))> 0){
		if(fwrite(buffer, 1, s, output_file) != s){
			perror("Output File Make Error");
		}
	}

	char* err_name = (char*)malloc(sizeof(char)*15);
	sprintf(err_name, "%s/error%d", dir_name, file_num);
	FILE* err_file = fopen(err_name, "wb");

	if(err_file == NULL){
		perror("get_info: Error-file error");
		exit(1);
	}

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
run_gcov(char* source, int idx){
	pid_t gcov_child = fork();

#ifdef DEBUG
	printf("[DEBUG] run_gcov: source %s\n", source);
#endif

	char* s_path = (char*)malloc(sizeof(char) * 1024);
	sprintf(s_path, "%s%s", fuzz_config.source_path, fuzz_config.sources[idx]);

#ifdef DEUBG
	printf("[DEBUG] run_gcov: sourcessss %s\n", s_path);
#endif

	if(gcov_child == 0){
		if(fuzz_config.curr_dir == 1){
			execl("/usr/bin/gcov", "gcov", "-b", "-c", source, NULL);
			perror("run_gcov: Execution Error!");
		}
		else{
			execl("/usr/bin/gcov", "gcov", "-b", "-c", s_path, NULL);
			perror("run_gcov: Execution Error!");
		}		
		return;
	}
	else if(gcov_child > 0){
		int exit_code;
		wait(&exit_code);
		free(s_path);
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

void 
show_result(int* return_code, int* prog_results, int trial){
	for(int i=0; i<trial; i++){
		printf("[%d] Return code: %d, Result: %d\n", i, return_code[i], prog_results[i]);
	}	
}

void
show_gcov(int* return_code, gcov_t* gcov_result, int trial){
	printf("===================================Fuzzer Summary====================================\n");
	for(int i=0; i<trial; i++){
		printf("[Input %d] Line: %d/%d Union: %d Latio:%lf   Branch: %d/%d Union: %d Latio:%lf\n", i, gcov_result[i].line, gcov_line_for_ratio ,gcov_result[i].union_line, (double)gcov_result[i].union_line/gcov_line_for_ratio, gcov_result[i].branch_line, gcov_line_for_branch, gcov_result[i].branch_union_line, (double)gcov_result[i].branch_union_line/gcov_line_for_branch );
	}
	printf("=====================================================================================\n");
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

	for(int i = 0; i < fuzz_config.trial; i++){
		char* input = (char*)malloc(sizeof(char)*(fuzz_config.f_max_len + 1)); 

		int fuzz_len;
		if(fuzz_config.mutation > 0){
			printf("[DEBUG] i: %d mute: %d file num: %d\n", fuzz_config.mutation, i,  i%fuzz_config.mutation);
			fuzz_len = mutational_input(input, input_files[i%(fuzz_config.mutation)], 0);			// Generate Mutational Input
		}
		else{
			fuzz_len = create_input(&fuzz_config, input); // Generage Random Input
		}

		printf("[Trial %d]Input: %s\n", i, input);

		if(gcov_flag == 1) 
			fuzz_config.cmd_args[fuzz_config.option_num + 1] = input; 

#ifdef DEBUG
	for(int i=0; i<3; i++){
		printf("[execute_prog] cmd_args[%d]: %s\n", i, fuzz_config.cmd_args[i]);
	}
#endif
		return_code[i] = run(&fuzz_config, input, fuzz_len, dir_name, i);

		if(gcov_flag == 1){
			for(int n_src=0; n_src<fuzz_config.number_of_source; n_src++){ // TODO sources
				run_gcov(fuzz_config.sources[n_src], n_src);
				if(i==0){
					gcov_line[n_src] = get_gcov_line(fuzz_config.sources[n_src], &gcov_line_for_ratio, &gcov_line_for_branch);
					printf("[DEBUG] fuzzer_main, lines:%d\n", gcov_line[n_src]);
					bitmap[n_src] = (int*)malloc(sizeof(int) * gcov_line[n_src]);
					memset(bitmap[n_src], 0, sizeof(int)*gcov_line[n_src]);

					branch_bitmap = (int*)malloc(sizeof(int) * gcov_line[n_src]);
					memset(branch_bitmap[n_src], 0, sizeof(int) * gcov_line[n_src]);
				}
				int new_mutate = 0;
				read_gcov_coverage(fuzz_config.sources[n_src], gcov_results, i, gcov_line, bitmap, branch_bitmap, &new_mutate);
				if(new_mutate == 1){
					printf("[DEBUG] new_mutate_inp\n");
					fuzz_config.mutation++;
					sprintf(input_files[fuzz_config.mutation-1], "%s/input%d", config->mutation_dir, fuzz_config.mutation); 

					char* input_name = (char*)malloc(sizeof(char)*25);
					sprintf(input_name, "%s/input%d", fuzz_config.mutation_dir, fuzz_config.mutation);
					FILE* new_inp_file = fopen(input_name, "wb");
					printf("[DEBUG] new_inp_file: %s\n", input_name);

					if(new_inp_file == NULL){
						perror("new_mutate: FILE Open Failed");
					}

					printf("[DEBUG] new_inp: %sn_srcn", input);	
					fwrite(input, 1, fuzz_len, new_inp_file);
					free(input_name);
					fclose(new_inp_file);
				}
				gcda_remove(fuzz_config.sources[n_src]);
			}
		}	

		free(input);
		fuzz_config.oracle(dir_name, i, prog_results, return_code[i]);
	}

	if(gcov_flag == 1){
		show_result(return_code, prog_results, fuzz_config.trial);
		show_gcov(return_code, gcov_results, fuzz_config.trial);
	}
	else{
		show_result(return_code, prog_results, fuzz_config.trial);
	}

	free(prog_results);
	free(return_code);
	free(gcov_results);
}
