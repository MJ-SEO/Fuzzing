#include "../include/http_program.h"

int main(){

//	char* url = "http://www.google.com/search?q=fuzzing#frag";
	char* url = "https://www.fuzzingbook.org/html/MutationFuzzer.html";

	http_program(url);	
	
	return 0;    
}
