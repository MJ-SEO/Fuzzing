#include "../include/mutating.h"
#include <time.h>

#define DEBUG

static int8_t interesting_8[] = { INTERESTING_8 };
static int16_t interesting_16[] = { INTERESTING_8, INTERESTING_16 };
static int32_t interesting_32[] = { INTERESTING_8, INTERESTING_16, INTERESTING_32 };

int
insert_random_character(char* seed, char* mutated_inp, int length, int offset, int byte){

	memcpy(mutated_inp, seed, sizeof(char) * length);
	
	for(int i=0; i<byte; i++){
		char rand_char = rand()%95 + 32; // 32 ~ 127
		mutated_inp[offset+i] = rand_char;
	}

	for(int i=offset+byte; i<length+byte; i++){
		mutated_inp[i] = seed[i-byte];
	}

	mutated_inp[length+byte] = 0x0;

	return length+byte;
}

int
insert_known_integer(char* seed, char* mutated_inp, int length, int offset, int byte){
	
	memcpy(mutated_inp, seed, sizeof(char) * length);	// TODO
	
	switch(byte){
		case 1:
			*(int8_t*)(mutated_inp + offset) = interesting_8[rand()%9];
			break;
		case 2:
			*(int16_t*)(mutated_inp + offset) = interesting_16[rand()%19];
			break;
		case 4:
			*(int32_t*)(mutated_inp + offset) = interesting_32[rand()%27];
			break;
		default:
			perror("");
			exit(1);
	}
	
	for(int i=offset+byte; i<length+byte; i++){
		mutated_inp[i] = seed[i-byte];
	}

	mutated_inp[length + byte] = 0x0;

	return length+byte;
}

int
delete_random_character(char* seed, char* mutated_inp, int length, int offset, int byte){
	if(length < 1) {
		perror("delete_random_character: length error");
		return length;
	}

	memcpy(mutated_inp, seed, length);
	
	int del_counter = 0;

	for(int i=0; i<byte; i++){
		if(byte > length - offset){
			i++;
			continue;
		}
		mutated_inp[offset+i] = 127;
		del_counter++;
	}
	
	mutated_inp[length] = 0x0;

	return length-del_counter;
}

int
change_random_bits(char* seed, char* mutated_inp, int length, int offset, int byte){
	if(length < 1){
		perror("change_random_bits: length error");
		return length;
	}

	char target = seed[offset];
	int shift = 0;
	switch(byte){ 				// TODO optimize?
		case 1:
			shift = rand()%7;
			break;
		case 2:
			shift = rand()%7+1;
			break;
		case 4:
			shift = rand()%7+3;
			break;
	}

	int bit = 1 << shift;
	
	for(int i=1; i<byte; i++){
		bit = bit | (1 << (shift + 1));
	}

	char new_c = (char) target ^ bit;

	memcpy(mutated_inp, seed, sizeof(char) * length);
	mutated_inp[offset] = new_c;
	mutated_inp[length] = 0x0;

	return length;
}

int
change_random_bytes(char* seed, char* mutated_inp, int length, int offset, int byte){
	if(length < 1){
		perror("change_random_bits: length error");
		return length;
	}
		
	memcpy(mutated_inp, seed, sizeof(char) * length);
	
	for(int i=0; i<byte; i++){
		char target = seed[offset + i];
		char new_c = (char)(target ^ 0xff);
	
		mutated_inp[offset + i] = new_c;	
	}

	mutated_inp[length] = 0x0;	

	return length;
}

int
change_simple_arith(char* seed, char* mutated_inp, int length, int offset, int byte){
	if(length < 1){
		perror("change_simple_arith: length error");
		return length;
	}

	memcpy(mutated_inp, seed, length);
	
	for(int i=0; i<byte; i++){
		int arith = rand()%71 -35;
		char new_c = seed[offset+i] + arith;
		mutated_inp[offset+i] = new_c;
	}

	return length;
}

int
change_known_integer(char* seed, char* mutated_inp, int length, int offset, int byte){
	if(length < 1){							// TODO
		perror("change_known_integer: length error");
		return length;
	}

	memcpy(mutated_inp, seed, length);
	
	switch(byte){
		case 1:
			*(int8_t*)(mutated_inp + offset) = interesting_8[rand()%9];
			break;
		case 2:
			*(int16_t*)(mutated_inp + offset) = interesting_16[rand()%19];
			break;
		case 4:
			*(int32_t*)(mutated_inp + offset) = interesting_32[rand()%27];
			break;
		default:
			perror("change_known_integer: out of bound");
			exit(1);
	}

	return length;
}

int
insert_mutation(char* seed, char* mutated_inp, int inp_len, int offset, int byte){
	int mutator = rand()%1+1;
	
	if((offset + byte) >= SEED_MAX){				 // TODO more...
		perror("insert_mutation: offset overflow");
		return inp_len;	
	}

	switch(mutator){
		case 1:
#ifdef DEBUG
	printf("[Mutating] Insert Random Character offset: %d, byte:%d\n", offset, byte);
#endif
			return insert_random_character(seed, mutated_inp, inp_len, offset, byte);
			break;
		case 2:
#ifdef DEBUG
	printf("[Mutating] Insert Known Integer offset: %d, byte:%d\n", offset, byte);
#endif
			return insert_known_integer(seed, mutated_inp, inp_len, offset, byte);
			break;
		default:
			perror("insert_mutation: out of bound");
			return inp_len;
	}
}

int
change_mutation(char* seed, char* mutated_inp, int inp_len, int offset, int byte){
	int mutator = rand()%3+1;
	
	if((offset + byte) > SEED_MAX){				 // TODO more...
		perror("change_mutation: offset overflow");
		return inp_len;	
	}
	
	switch(mutator){
		case 1:
#ifdef DEBUG
	printf("[Mutating] Change Random Bits offset: %d, byte:%d\n", offset, byte);
#endif
			return change_random_bits(seed, mutated_inp, inp_len, offset, byte);
			break;
		case 2:
#ifdef DEBUG
	printf("[Mutating] Change Random Bytes offset: %d, byte:%d\n", offset, byte);
#endif
			return change_random_bytes(seed, mutated_inp, inp_len, offset, byte);
			break;
		case 3:
#ifdef DEBUG
	printf("[Mutating] Change Simple Arith offset: %d, byte:%d\n", offset, byte);
#endif
			return change_simple_arith(seed, mutated_inp, inp_len, offset, byte);
			break;
		case 4:
#ifdef DEBUG
	printf("[Mutating] Change Known Integer offset: %d, byte:%d\n", offset, byte);
#endif
			return change_known_integer(seed, mutated_inp, inp_len, offset, byte);
			break;
		default:
			perror("change_mutation: out of bound");
			return inp_len;
	}
}

int 
delete_mutation(char* seed, char* mutated_inp, int inp_len, int offset, int byte){
	
	if((offset + byte) > SEED_MAX){
		perror("delete_mutation: offset overflow");
		return inp_len;	
	}
#ifdef DEBUG
	printf("[Mutating] Delete Random Character offset: %d, byte:%d\n", offset, byte);
#endif
	return delete_random_character(seed, mutated_inp, inp_len, offset, byte);
}

int
mutate(char* seed, char* mutated_inp, int inp_len){
	int len;	
	int offset = rand()%inp_len;
	int mutate_mode = rand()%7+1;
	int byte_size[3] = {1, 2, 4};
	int byte = rand()%3;
	
	if(mutate_mode <= 2){
		len = insert_mutation(seed, mutated_inp, inp_len, offset, byte_size[byte]);	
	}
	else if(mutate_mode >= 3 && mutate_mode <= 6){
		len = change_mutation(seed, mutated_inp, inp_len, offset, byte_size[byte]);
	}
	else{
		len = delete_mutation(seed, mutated_inp, inp_len, offset, byte_size[byte]);
	}
	
	return len;
}


int main(){					// TEST DRIVER for mutating
	srand((unsigned int)time(NULL));
	int len = 0;
	
	for(int i=0; i<13; i++){
		char* seed = "https://www.google.com";
		int length = strlen(seed);
		char* mutated_inp = (char*)malloc(sizeof(char) * 1024);
		memset(mutated_inp, 0, 1024);

		len = mutate(seed, mutated_inp, length);
		
		printf("[RESULT]: %s(%d) / %ld\n\n", mutated_inp, len, strlen(mutated_inp));	
		free(mutated_inp);
	}
}

