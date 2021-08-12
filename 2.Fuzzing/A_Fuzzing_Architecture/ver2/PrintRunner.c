#include "PrintRunner.h"

int
run(Runner * runner, char* input, int input_size){
	if(input_size < 0){
		perror("Negative Input Size Error\n");
		return -1;
	}

	runner->input = (char*)malloc(sizeof(char) * input_size);	
	if(runner->input == NULL){
		perror("Alloc failed\n");
		return -1;
	}
	
	for(int i=0; i<input_size; i++){
		runner->input[i] = input[i];
		putc(runner->input[i], stdout);
	}

	runner->outcome = UNRESOLVED;
	return 1;
}

int 
free_input(Runner runner){
	if(runner.input_size == 0) {
		perror("NULL space\n");
		return -1;
	}
	free(runner.input);
	return 1;
}

void PrintRunner_init(Runner * runner){
	runner->run = run;
	runner->free_input = free_input;
}	

int main(){
	Runner print_runner;
	PrintRunner_init(&print_runner);	

	char input[] = "help\0 me!! plz\n";	
	runner.run(&print_runner, input, sizeof(input));

//	printf("[DEBUG] %s %s\n", runner.input, runner.outcome);
	free_input(runner);	
	return 0;
}
