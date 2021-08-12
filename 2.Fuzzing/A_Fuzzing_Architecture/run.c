#include "run.h"
#include "fuzzer.h"

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
	
	char* data = RandomFuzzer(20, 20, START, RANGE);
	write(in_pipes[1], data, strlen(data));
	close(in_pipes[1]);

	char buffer[1024];
	ssize_t s;

	while((s = read(out_pipes[0], buffer, 1023) > 0)){
		strcpy(self->sout, buffer);
	}

	while((s = read(err_pipes[0], buffer, 1023) > 0)){
		strcpy(self->serr, buffer);
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
	int in_pipes[2];
	int out_pipes[2];
	int err_pipes[2];
	
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
run(test_config_t * config, char* input){
	printf("Hello run\n");

/*	self->program = program;
	run_process(self);
	
	if(self->returncode == 0) strcpy(self->outcome, "PASS");
	else if(self->returncode < 0) strcpy(self->outcome, "FAIL");
	else strcpy(self->outcome, "UNRESOLVED");

	printf("(CompletedProcess(args = '%s', returncode = %d, stdout ='%s', stderr='%s'),'%s')\n", self->program, self->returncode, self->sout, self->serr, self->outcome);
	return;
*/
}

