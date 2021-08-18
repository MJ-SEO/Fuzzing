#include "cgi_decoder.c"
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct coverage{
	char c_file[30];
	int line_number;
} coverage_t;

void 
compile_cgi(char* target){
	pid_t child = fork();
	if(child == 0){
		execl("/usr/bin/gcc", "gcc", "--coverage", "-o", "cgi_decode", target, NULL); 
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
exec_cgi(char* target){
	pid_t child = fork();
	if(child == 0){
		execl("./cgi_decode", "cgi_decode", "Send+mail+to+me%40fuzzingbook.org", NULL);
		perror("Excution Error!");
		exit(1);
	}
	else if(child > 0){
		int exit_code;
		wait(&exit_code);
		if(exit_code != 0){
			perror("CGI Execute Error!");
			exit(1);
		}
	}
	else{
		perror("[exec_cgi] Fork Error!");
		exit(1);
	}
}

void
exec_gcov(char* target){
	pid_t child = fork();
	if(child == 0){
		execl("/usr/bin/gcov", "gcov", target, NULL); 
		perror("Excution Error!");
		exit(1);
	}
	else if(child > 0){
		int exit_code;
		wait(&exit_code);
		if(exit_code != 0){
			perror("CGI Execute Error!");
			exit(1);
		}
	}
	else{
		perror("[exec_cgi] Fork Error!");
		exit(1);
	}
}

void
testing(){
	char* buf = cgi_decode("Hello%2c+World%21");
	printf("%s\n", buf);
}

void
blackbox_testing(){
	assert(strcmp(cgi_decode("+")," ") == 0);
	assert(strcmp(cgi_decode("%20"), " ") == 0);
	assert(strcmp(cgi_decode("abc"), "abc") == 0);
	
	assert((cgi_decode("%?a")) == NULL);
}

void
read_gcov_coverage(char* c_file){
	char gcov_file[30];
	strcpy(gcov_file, c_file);
	strcat(gcov_file, ".gcov");

	FILE* fp;
	fp = fopen(gcov_file, "rb");
	if(fp == NULL){
		perror("File Open Error!");
		exit(1);
	}

	ssize_t ret;
	char* line;
	size_t size = 0;
	char* delim = ":";

	coverage_t* cov_list = (coverage_t*)malloc(sizeof(coverage_t) * 100); // Linked list?
	int index = 0;

	while((ret = getline(&line, &size, fp))!= -1){
//		printf("line: %s", line);
		char * ptr = strtok(line, delim);
		int flag = 0;
		while(ptr != NULL){
		//	printf("[DEBUG] [%d] ptr:%s\n", flag, ptr);
			if(flag == 0 && atoi(ptr) == 0) break;

			if(flag == 1){
				strcpy(cov_list[index].c_file, c_file);
				cov_list[index].line_number = atoi(ptr);
				index++;		
			}

			ptr = strtok(NULL, delim);
			flag++;
		}
	}

	for(int i=0; i<index; i++){
		printf("%s %d\n", cov_list[i].c_file, cov_list[i].line_number);
	}
	
	fclose(fp);
}

int main(){
	testing();
	
	blackbox_testing();
	
	compile_cgi("cgi_test.c");
	exec_cgi("cgi_test.c");
	exec_gcov("cgi_test.c");
	
	read_gcov_coverage("cgi_test.c");
}

