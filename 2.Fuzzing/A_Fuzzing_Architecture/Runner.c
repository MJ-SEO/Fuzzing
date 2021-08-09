#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct runner{
	char* inp;
	char* outcome;
} runner;

runner* 
init(runner* self){
	runner* temp = (runner*)malloc(sizeof(runner) * 1);
	temp->inp = "init";
	temp->outcome = "PASS";
	
	return temp;
}

void
free_runner(){
	return;
}

void
runn(runner* self, char* input){
	printf("[INPUT] %s\n", input);
	self->inp = input;
	self->outcome = "UNRESOLVED";
}


int main(){
	runner* p = init(p);
	printf("[DEBUG] %s %s\n", p->inp, p->outcome);
	
	runn(p, "Some Input");
	printf("[DEBUG] %s %s\n", p->inp, p->outcome);
	
	return 0;
}
