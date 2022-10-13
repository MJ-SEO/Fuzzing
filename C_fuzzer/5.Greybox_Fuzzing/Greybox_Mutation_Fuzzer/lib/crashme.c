#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(){
	char* inp = (char*)malloc(sizeof(char)*100);
	scanf("%s", inp);

	if(strlen(inp) > 0 && inp[0] == 'b'){
		if(strlen(inp) > 1 && inp[1] == 'a'){
			if(strlen(inp) > 2 && inp[2] == 'd'){
				if(strlen(inp) > 3 && inp[3] == '!'){
					assert(0);
				}
			}
		}
	}

	return 0;
}
