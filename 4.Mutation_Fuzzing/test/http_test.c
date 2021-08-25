#include "../include/http_program.h"

int main(){
	char* test_url = (char*)malloc(sizeof(char) * 1024); // = "http://www.google.com/search?q=fuzzing";
	scanf("%s", test_url);
	printf("[DEBUG] url: %s\n", test_url);	

	http_program(test_url);	

	free(test_url);
	return 0;    
}
