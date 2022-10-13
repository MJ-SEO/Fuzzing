#include "../include/make_gcov.h"

void 
compile_cgi(char* target, char* fname){
	pid_t child = fork();
	if(child == 0){
		execl("/usr/bin/gcc", "gcc", "--coverage", "-o", fname, target, NULL); 
		perror("Excution Error!");
		exit(1);
	}
	else if(child > 0){
		int exit_code;
		wait(&exit_code);
		if(exit_code != 0){
			perror("CGI Compile Error!");
			exit(1);
		}
	}
	else{
		perror("[compile_cgi] Fork Error!");
		exit(1);
	}
}

void
exec_cgi(char* fname, char* args){
	pid_t child = fork();
	char* exec_name = (char*)malloc(sizeof(char) * strlen(fname) + 3);
	sprintf(exec_name, "./%s", fname);
	if(child == 0){
		execl(exec_name, fname, args, NULL); // TODO input..
		perror("Excution Error!");
		exit(1);
	}
	else if(child > 0){
		int exit_code;
		wait(&exit_code);
		if(exit_code != 0){
			perror("CGI Execute Error!");
			free(exec_name);
			exit(1);
		}
	}
	else{
		perror("[exec_cgi] Fork Error!");
		exit(1);
	}
	free(exec_name);
}

void
exec_gcov(char* target){
	pid_t child = fork();
	char* c_file = (char*)malloc(sizeof(char) * strlen(target) + 3);
	sprintf(c_file, "%s.c", target);

	if(child == 0){
		execl("/usr/bin/gcov", "gcov", c_file, NULL); 
		perror("Excution Error!");
		exit(1);
	}
	else if(child > 0){
		int exit_code;
		wait(&exit_code);
		if(exit_code != 0){
			perror("GCOV Execute Error!");
			exit(1);
		}
	}
	else{
		perror("[exec_cgi] Fork Error!");
		exit(1);
	}
	free(c_file);
}

void
make_gcov(char* path, char* fname, char* args){
	compile_cgi(path, fname);	
	exec_cgi(fname, args);	
	exec_gcov(fname);	
}
