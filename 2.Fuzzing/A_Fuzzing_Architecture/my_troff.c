#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define DSIZE 1024

int main(){
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	ssize_t s;
	int len = 0;

	char* data = (char*)malloc(sizeof(char) * DSIZE);
	int size = DSIZE;

	while((s = fread(buf, 1, 1, stdin)) > 0){
		data[len] = buf[0];
		len += s;
		if(len >= size){
			size *= 2;
			data = (char*)realloc(data, size);
		}
	}

	printf("%s", data);
	
	for(int i=0; i<len; i++){
		if(i>0 && data[i] == '\n'){
			if(data[i-1] == '.'){
				perror("No_dot_Failures");
				return 1;
			}
			if(data[i-1] > 127 || data[i-1] < 0){ 			
				perror("No_8bit_Failures\n");
				return 2;
			}
		}
		else if(data[i] == '\\' && i <= len-2){
			if(data[i+1] == 'D'){
				if(data[i+2] <= 31){
					perror("No_Backslash_D_Failures\n");
					return 3;
				}		
			}
		}
	}

	return 0;
}
