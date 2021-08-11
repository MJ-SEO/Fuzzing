#include "PrintRunner.h"

int
run(Runner * runner, char* input, int input_size){
	runner->input = (char*)malloc(sizeof(char) * input_size);	
	printf("[INPUT] %s\n", input);	
	
	for(int i=0; i<input_size; i++){
		runner->input[i] = input[i];
	}

	runner->outcome = UNRESOLVED;
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
	Runner runner;
	PrintRunner_init(&runner);	

	char input[] = "hello";	
	runner.run(&runner, input, sizeof(input));

	printf("[DEBUG] %s %s\n", runner.input, runner.outcome);

	free_input(runner);	
	return 0;
}
