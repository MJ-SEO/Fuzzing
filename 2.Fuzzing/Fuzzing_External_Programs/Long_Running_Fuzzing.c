#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int pipes[2];
int error_pipes[2];
int pass[101];

char*
fuzzer(int max_length, int start, int range){
	int len = (rand()%max_length+1)+1;
	char* out = (char*)malloc(sizeof(char) * len);
	for(int i=0; i<len; i++){
		out[i] = (char)((rand()%range) + start);
	}
	out[len-1] = '\0';
	return out;
}

void 
child_proc(char* path){
	close(pipes[0]);
	close(error_pipes[0]);

	int devnull = open("/dev/null",O_RDONLY);  
	dup2(devnull, 0);
	dup2(pipes[1], 1);
	dup2(error_pipes[1], 2);

	execlp("bc", "bc", path, NULL);	
}

void
parent_proc(char* tempdir, int num){
	int exit_code;
	pid_t term_pid = wait(&exit_code);
//	printf("Process %d is exit with %d\n", num, exit_code);
	
	close(pipes[1]);
	close(error_pipes[1]);
	
	char buf[1024];
	ssize_t s;
	char *output = (char*)malloc(sizeof(char) * 50);
	sprintf(output, "%s/output%d", tempdir, num);
	FILE* outf = fopen(output, "wb");

	while((s = read(pipes[0], buf, 1023)) > 0){
		fwrite(buf, 1, s, outf);
		pass[num] = 1;
	}
	fclose(outf);
	
	char *error = (char*)malloc(sizeof(char) * 50);
	sprintf(error, "%s/error%d", tempdir, num);
	FILE* errf = fopen(error, "wb");
	
	while((s =read(error_pipes[0], buf, 1023)) > 0){
		fwrite(buf, 1, s, errf);
		pass[num] = 2;
	}
	fclose(errf);
	
	close(pipes[0]);
	close(error_pipes[0]);
	free(output);
	free(error);
	return;
}

void 
subproc(char* path, char* tempdir, int num){

	if(pipe(pipes) < 0){
		perror("pipe error\n");
		exit(1);
	}
	
	if(pipe(error_pipes) < 0){
		perror("pipe error\n");
		exit(1);
	}

	pid_t child = fork();
	if(child == 0){
		child_proc(path);
	}
	else if (child > 0){
		parent_proc(tempdir, num);	
	}
	else{
		printf("fork error\n");
		exit(1);
	}
	
	return;
}

void 
long_running_fuzzing(){
	
	char template[] = "tmp.XXXXXX";
	char *tempdir = mkdtemp(template);	
	
	for(int i=1; i<=100; i++){
		char basename[10];
		sprintf(basename, "input%d", i);
		char *data = fuzzer(100, 32, 32);
		strcat(data, "\n");

		char my_file[40];
		strcpy(my_file, tempdir);
		strcat(my_file, "/");
		strcat(my_file, basename);

		FILE *fp;
		fp = fopen(my_file, "wb");
		if(fp == NULL){
			fputs("File Error\n", stderr);
			exit(1);
		}
		fwrite(data, 1, strlen(data), fp);
		fclose(fp);
	
		//printf("[DEBUG] myfile: %s\n", my_file);
		subproc(my_file, tempdir, i);
	}
}

void
print_result(){
	int err = 0;
	int output = 0;
	int etc = 0;
	for(int i=1; i<=100; i++){
		if(pass[i] == 0){
			etc++;
		}
		else if(pass[i] == 1){
			output++;
		}
		else{
			err++;
		}	
	}
	printf("Error:%d Output:%d Etc:%d\n", err, output, etc); 
}

int main(){
	srand((unsigned int)time(NULL));
	long_running_fuzzing();
	print_result();
}
