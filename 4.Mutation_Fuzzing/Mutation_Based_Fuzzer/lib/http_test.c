#include "../include/http_program.h"

int main(){
	char* url = (char*)malloc(sizeof(char) * 1024);	// ..?
	scanf("%s", url);
	printf("[DEBUG] Received URL:%s\n", url);	
	http_program(url);	
	free(url);
	return 0;    
}
