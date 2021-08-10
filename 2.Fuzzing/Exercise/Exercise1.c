#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
backslashD(char* str){
	char* pattern = "\\D";
	int len = strlen(str);

	char* index = strstr(str, pattern);
	if(index == NULL || strlen(index) strlen(str))

}

int main(){
	char* str = "A Garden Diary";
	printf("[D] str:%s, %ld\n", str, strlen(str));

	char* ptr;
	ptr = strstr(str, "den");
	
	printf("[D] str:%s, %ld\n", ptr, strlen(ptr));
	return 0;
}
