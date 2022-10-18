#include "../include/fuzzer.h"
#include "../include/create_input.h"
#include "../include/coverage.h"

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
static int gcov_flag;

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

	if(config->cmd_args != NULL) {
		if(config->source != 0x0){
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
		if(config->source != 0x0){
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

	fuzz_config.timeout = config->timeout;

	fuzz_config.oracle = config->oracle;

	if(config->source != 0x0){
		assert(access(config->source_path, F_OK) == 0 && "Target Source Not Exiset!");	
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


	execv(config->binary_path, config->cmd_args);
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
		execl("/usr/bin/gcov", "gcov", "-b", "-c", source, NULL);
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

void 
show_result(int* return_code, int* prog_results, int trial){
	for(int i=1; i<=trial; i++){
		printf("[%d] Return code: %d, Result: %d\n", i, return_code[i], prog_results[i]);
	}	
}

void
show_gcov(int* return_code, gcov_t* gcov_result, int trial){
	int pass = 0;
	int fail = 0;
	printf("==========================================Trial==========================================\n");
	for(int i=1; i<=trial; i++){
		if(return_code[i] == 0) pass++;
		else fail++;
		printf("[Input %d] Line: %d/%d Total: %d Latio:%lf   Branch: %d/%d Total: %d Latio:%lf\n", i, gcov_result[i].line, gcov_line_for_ratio ,gcov_result[i].union_line, (double)gcov_result[i].union_line/gcov_line_for_ratio, gcov_result[i].branch_line, gcov_line_for_branch, gcov_result[i].branch_union_line, (double)gcov_result[i].branch_union_line/gcov_line_for_branch );
	}
	printf("=========================================================================================\n");

	printf("\n===========================Fuzzing Summary===========================\n");
	printf("* Trial : %d\n", trial);
	printf("* Pass  : %d\n", pass);
	printf("* Fail  : %d\n", fail);
	printf("* Line Coverage : (%d/%d) %lf\n", gcov_result[trial].union_line, gcov_line_for_ratio, (double)gcov_result[trial].union_line / gcov_line_for_ratio);
	printf("* Branch Coverage : (%d/%d) %lf\n", gcov_result[trial].branch_union_line, gcov_line_for_branch, (double)gcov_result[trial].branch_union_line / gcov_line_for_branch );
	printf("=====================================================================\n");

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
		
		if(gcov_flag == 1) 
			fuzz_config.cmd_args[fuzz_config.option_num + 1] = input; 
		
		return_code[i] = run(&fuzz_config, input, fuzz_len, dir_name, i);
		free(input);

		if(gcov_flag == 1){
			run_gcov(fuzz_config.source);
			if(i==1){
				gcov_line = get_gcov_line(fuzz_config.source);
				bitmap = (int*)malloc(sizeof(int) * gcov_line);
				memset(bitmap, 0, sizeof(int)*gcov_line);
				
				branch_bitmap = (int*)malloc(sizeof(int) * gcov_line);
				memset(branch_bitmap, 0, sizeof(int) * gcov_line);
			}
			read_gcov_coverage(fuzz_config.source, gcov_results, i);
			gcda_remove(fuzz_config.source);
		}	

		fuzz_config.oracle(dir_name, i, prog_results, return_code[i]);
	}

	if(gcov_flag == 1){
		show_gcov(return_code, gcov_results, fuzz_config.trial);
	}
	else{
		show_result(return_code, prog_results, fuzz_config.trial);
	}



	free(prog_results);
	free(return_code);
	free(gcov_results);
}
