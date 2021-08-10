#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <assert.h>

#include "../fuzzer.h"

#define MIN_LAN 10

int in_pipes[2];
int out_pipes[2];
int err_pipes[2];

typedef struct prunner{
	char* outcome;
	char* program;
	char* sout;
	char* serr;
	int returncode;
}prunner;

char* 
RandomFuzzer(int min_len, int max_len, int start, int range){
	int len = rand()%(max_len - min_len + 1) + min_len;
	char* out = (char*)malloc(sizeof(char)*len);
	for(int i=0; i<len; i++){
		out[i] = rand()%range + start;
	}
	return out;
}

prunner*
init(){
	prunner* p = (prunner*)malloc(sizeof(prunner) * 1);
	p->outcome = "FAIL";
	p->program = "";
	p->sout = "";
	p->serr = "";
	p->returncode = -1;
	return p;
}

void
child_proc(prunner* self){
	dup2(in_pipes[0], 0);
	close(in_pipes[0]);
	close(in_pipes[1]);

	close(out_pipes[0]);
	close(err_pipes[0]);

	dup2(out_pipes[1], 1);
	dup2(out_pipes[1], 2);

	execlp(self->program, self->program, NULL);
}

void
parent_proc(prunner* self){
	close(out_pipes[1]);
	close(err_pipes[1]);
	
	char* data = RandomFuzzer(MIN_LAN, MAX_LEN, START, RANGE);
	write(in_pipes[1], data, strlen(data));
	close(in_pipes[1]);

	char buffer[1024];
	ssize_t s;

	while((s = read(out_pipes[0], buffer, 1023) > 0)){
		self->sout = buffer;
	}

	while((s = read(err_pipes[0], buffer, 1023) > 0)){
		self->serr = buffer;
	}

	close(out_pipes[0]);
	close(err_pipes[0]);

	int exit_code;
	pid_t term_pid = wait(&exit_code);
	self->returncode = exit_code;
	
	return;
}

void
run_process(prunner* self){
	if(pipe(in_pipes) < 0){
		perror("pipe error\n");
		exit(1);
	}	
	if(pipe(out_pipes) < 0){
		perror("pipe error\n");
		exit(1);
	}	
	if(pipe(err_pipes) < 0){
		perror("pipe error\n");
		exit(1);
	}	

	pid_t child = fork();
	if(child == 0){
		child_proc(self);
	}
	else if(child > 0){
		parent_proc(self);
	}
	else{
		perror("fork error\n");
		exit(1);
	}

	return;
}

void 
runner(prunner* self, char* program){
	self->program = program;
	run_process(self);
	
	if(self->returncode == 0) self->outcome = "PASS";
	else if(self->returncode < 0) self->outcome = "FAIL";
	else self->outcome = "UNRESOLVED";

	printf("(CompletedProcess(args = '%s', returncode = %d, stdout ='%s', stderr='%s'),'%s')\n", self->program, self->returncode, self->sout, self->serr, self->outcome);
	return;
}

void
runs(char* program, int num){
	for(int i=0; i<num; i++){
		prunner* p = init();	
		runner(p, program);
		free(p);
	}
}

int main(){
	srand((unsigned int)time(NULL));	

	for(int i=0; i<10; i++){
		char* data = RandomFuzzer(MIN_LAN, MAX_LEN, START, RANGE);
		prunner * p = init();
		runner(p, "cat");
	//	printf("[DEBUG] %s\n", p->sout);
	//	assert(strcmp(p->sout, data) == 0);
		assert(strcmp(p->outcome, "PASS") == 0);
		free(p);
	}

	prunner * p = init();
	runner(p, "cat");
	free(p);

	printf("==============================\n");
	runs("cat", 10);
	return 0;
}
