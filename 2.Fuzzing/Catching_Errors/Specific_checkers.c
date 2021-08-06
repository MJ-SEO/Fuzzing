#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <assert.h>

typedef struct map_air{
	char* code;
	char* airport;
	int size;
	int capacity;
} airport_code;

int 
code_repOK(char* code){
	assert(strlen(code) == 3 && "Airport code must have three characters");
	for(int i=0; i<strlen(code); i++){
		assert((isalpha(code[i]) > 0) && "Non-letter in airport code");
		assert((isupper(code[i]) > 1) && "Lowercase letter in airport code");
	}
	return 1;	
}

int 
airport_codes_repOK(airport_code* alist){
	for(int i=0; i<alist->size; i++){
		assert(code_repOK(alist[i].code));
	}
	return 1;
}

int 
add_new_airport(airport_code* alist, char* code, char* city){
	assert(code_repOK(code));
	assert(airport_codes_repOK(alist));

	if(alist->size == alist->capacity){
		alist->capacity *= 2;
		alist = (airport_code*)realloc(alist, alist->capacity);
	}	
	
	alist[alist->size].code = code;
	alist[alist->size].airport = city;
	alist->size++;

	assert(airport_codes_repOK(alist));
	return 1;
}

int 
airport_init(airport_code* alist){
	add_new_airport(alist, "YVR", "Vancouver");
	add_new_airport(alist, "JFK", "New York-JFK");
	add_new_airport(alist, "CDG", "Paris-Charles de Gaulle");
	add_new_airport(alist, "CAI", "Cairo");
	add_new_airport(alist, "LED", "St. Petersburg");
	add_new_airport(alist, "PEK", "Beijing");
	add_new_airport(alist, "HND", "Tokyo-Haneda");
	add_new_airport(alist, "AKL", "Auckland");
	return 1;
}

int main(){
	airport_code* alist = (airport_code*)malloc(sizeof(airport_code) * 10);
	alist->size = 0;
	alist->capacity = 10;

	airport_init(alist);
	airport_codes_repOK(alist);

	add_new_airport(alist, "BER", "Berlin");
//	add_new_airport(alist, "London-Heathrow", "LHR");
	add_new_airport(alist, "IST", "Istanbul Yeni Havaliman1");

	for(int i=0; i<alist->size; i++){
		printf("%s %s\n", alist[i].code, alist[i].airport);
	}
	
}
