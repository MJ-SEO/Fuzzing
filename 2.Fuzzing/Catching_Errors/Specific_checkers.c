#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char*
airport_codes(char* code){
	if(strcmp(code, "YVR") == 0){
		return "Vancouver";
	}
	else if(){

	}
	switch(code){
		case "YVR" :
			break;
		case "JFK" :
			return "New York-JKF";
			break;
		case "CDG" :
			return "Paris-Charles de Gaulle";
			break;
		case "CAI" :
			return "Cairo";
			break;
		case "LED" :
			return "St. Petersburg";
			break;
		case "PEK" :
			return "Beijing";
			break;
		case "HND" :
			return "Tokyo-Haneda";
			break;
		case "AKL" :
			return "Auckland";
			break;
		default :
			return "zz";
			break;
	}
}

int main(){
	printf("%s\n", airport_codes("YVR"));
}
