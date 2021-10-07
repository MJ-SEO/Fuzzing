#include <stdio.h> 
#include <string.h> 

int main(int argc, char * argv[]) {
	int cnt[26];
	char input[32] = ""; 
	int idx;  
	int check = 1; 
	memset(cnt, 0, sizeof(cnt));

	printf("Please enter a word: \n"); 
	gets(input); 

	for (int i = 0 ; i < 32; i++) 
	{ 
		if ( input[i] - 'a' >= 0 && input[i] - 'a' <= 25) {
			idx = input[i] - 'a' ; 
			cnt[idx]++; 
		} else if (input[i] - 'A' >= 0 && input[i] - 'A' <= 25) { 
			idx = input[i] - 'A' ; 
			cnt[idx]++; 
		} else {
			if (input[i] == '\0') break; 
			check = 0 ;
		}
	}

	if (!check) { 
		fprintf(stderr, "Please enter English Word!\n"); 
		return 0; 
	}
	for(int i = 0 ; i < 26 ; i++) {
		if ( cnt[i] != 0 ) { 
			printf("%c : %d\n", (char)(i + 'a'), cnt[i]) ; 
		}
	}

	return 0;
}
