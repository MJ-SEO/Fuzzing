#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int pipes[2];
int error_pipes[2];

typedef struct prunner{
	char* outcome;
	char* program;
	int returncode;
	char* sout;
	char* serr;
} prunner;

prunner* rtable;

prunner* 
init(prunner* self, char* program){
	prunner* temp = (prunner*)malloc(sizeof(prunner) * 1);
	temp->outcome = "PASS";
	temp->program = program;
	temp->returncode = 0;
	temp->sout = "";
	temp->serr = "";
	return temp;
}

void
free_prunner(){
	return;
}

void
child_proc(prunner* self, char* input){
	close(pipes[0]);
	close(error_pipes[0]);
	dup2(pipes[1], 1);
	dup2(error_pipes[1], 2);

	execlp(self->program, self->program, input, NULL);
}

void 
parent_proc(prunner* self){
	int exit_code;
	pid_t term_pid = wait(&exit_code);
	printf("Process %d is exit with %d\n", getpid(), exit_code);
	self->returncode = exit_code;

	close(pipes[1]);
	close(error_pipes[1]);

	char buf[1024];
	ssize_t s;
	while((s = read(pipes[0], buf, 1023)) > 0){
			printf("[STDOUT] %s\n", buf);
			self->sout = buf; //TODO append
	}

	while((s = read(error_pipes[0], buf, 1023)) > 0){
			printf("[STDERR] %s\n", buf);
			self->serr = buf;
	}
	return;
}

void
run_process(prunner* self, char* input){

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
		child_proc(self, input);
	}
	else if(child > 0){
		parent_proc(self);
	}
	else{
		perror("fork error\n");
	}
	return;	
}

void
runn(prunner* self, char* input){
	//prunner* result = (prunner*)malloc(sizeof(prunner) * 1);
	run_process(self, input);
	
	if(self->returncode == 0){
		self->outcome = "PASS";
	}
	else if(self->returncode < 0){
		self->outcome = "FAIL";
	}
	else{
		self->outcome = "UNRESOLVED";
	}

printf("(CompletedProcess(args = '%s', returncode = %d, stdout ='%s', stderr='%s'),'%s')\n", self->program, self->returncode, self->sout, self->serr, self->outcome);
}


int main(){
	prunner* p = init(p, "cat");
	printf("[DEBUG] %s %s %d\n", p->outcome, p->program, p->returncode);
	
	runn(p, "hello");
	//printf("[DEBUG] %s %s %d %s\n", p->outcome, p->program, p->returncode, p->sout);
	
	return 0;
}
