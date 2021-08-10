#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
backslashD(char* str){
	char* pattern = "\\D";

}

int main(){
	char* str = "A Garden Diary";
	printf("[D] str:%s, %ld\n", str, strlen(str));

	char* ptr;
	ptr = strstr(str, "den");
	
	printf("[D] str:%s, %ld\n", ptr, strlen(ptr));
	return 0;
}
