#include "../include/mutating.h"

#define DEBUG

static uint8_t interesting_8[] = { INTERESTING_8 };
static uint16_t interesting_16[] = { INTERESTING_8, INTERESTING_16 };
static uint32_t interesting_32[] = { INTERESTING_8, INTERESTING_16, INTERESTING_32 };

int
flip_random_character(char* seed, char* mutated_inp, int length){
#ifdef DEBUG
	printf("[Mutating] Flip_1bit\n");
#endif
	if(length < 1){
		perror("filp_random_character: length error"); // TODO return
		return length;
	}
	int pos;
	pos = rand()%length; // 0 ~ seedlen(seed)

	char c = seed[pos];
	int bit;
	bit = 1 << rand()%7;
	char new_c = c ^ bit;

	memcpy(mutated_inp, seed, sizeof(char) * length);
	mutated_inp[pos] = new_c;

	return length;
}

int
flip_two_bits(char* seed, char* mutated_inp, int length){
#ifdef DEBUG
	printf("[Mutating] Filp_2bits\n");
#endif
	if(length < 1){
		memcpy(mutated_inp, seed, sizeof(char) * length);
		return length;
	}

	int pos;
	pos = rand()%length;

	char c = seed[pos];
	int rand_bit = rand()%7;
	int bit;
	bit = 1 << rand_bit;
	bit = bit | 1 << rand_bit+1;

	char new_c = c ^ bit;

	memcpy(mutated_inp, seed, sizeof(char) * length);
	mutated_inp[pos] = new_c;

	return length;
}

int
flip_on_bytes(char* seed, char* mutated_inp, int length){
#ifdef DEBUG
	printf("[Mutating] Flip a bytes\n");
#endif
	if(length < 1){
		memcpy(mutated_inp, seed, sizeof(char) * length);
		return length;
	}

	int pos;
	pos = rand()%length;

	int bytes = rand()%3+1;
	unsigned int bit = 255;

	if(bytes == 3 && (length-pos) >= 4){
		memcpy(mutated_inp, seed, length);

		for(int i=0; i<4; i++){
			char c = seed[pos + i];
			char new_c = c ^ bit;
			mutated_inp[pos + i] = new_c;
		}

		return length;
	}
	else if(bytes == 2 && (length-pos) >= 2){
		memcpy(mutated_inp, seed, length);

		for(int i=0; i<2; i++){
			char c = seed[pos + i];
			char new_c = c ^ bit;
			mutated_inp[pos + i] = new_c;
		}

		return length;
	}
	else{
		memcpy(mutated_inp, seed, length);
		
		char c = seed[pos];
		char new_c = c ^ bit;
		mutated_inp[pos] = new_c;
		return length;
	}

	perror("flip_on_bytes: reached invalid");
	return -1;
}

int
simple_arithmetics(char* seed, char* mutated_inp, int length){
#ifdef DEBUG
	printf("[Mutating] Simple Arithmetics\n");
#endif
	if(length < 1){
		memcpy(mutated_inp, seed, sizeof(char) * length);
		return length;
	}

	int pos = rand()%length;

	int arith = rand()%71 -35;

	char new_c = (seed[pos] + arith);

	memcpy(mutated_inp, seed, length);

	mutated_inp[pos] = new_c;

	return length;

}

int
known_integers(char* seed, char* mutated_inp, int length){	// TODO test
#ifdef DEBUG
	printf("[Mutating] Known_Integers\n");
#endif
	if(length < 1){
		memcpy(mutated_inp, seed, sizeof(char) * length);
		return length;
	}

	int pos = rand()%length;

	int bytes = rand()%3+1;

	if(bytes == 3 && (length-pos) >= 4){

		memcpy(mutated_inp, seed, length);

#ifdef DEBUG
	printf("[Known] int:%d\n", interesting_32[rand()%27]);
#endif
		*(uint32_t*)(mutated_inp + pos) = interesting_32[rand()%27];

		return length;
	}
	else if(bytes == 2 && (length-pos) >= 2){

		memcpy(mutated_inp, seed, length);
#ifdef DEBUG
	printf("[Known] int:%d\n", interesting_16[rand()%19]);
#endif
		*(uint16_t*)(mutated_inp + pos) = interesting_16[rand()%19];

		return length;
	}
	else{

		memcpy(mutated_inp, seed, length);
#ifdef DEBUG
	printf("[Known] int:%d\n", interesting_8[rand()%9]);
#endif
		*(uint8_t*)(mutated_inp + pos) = interesting_8[rand()%9];

		return length;
	}

	perror("known_integers: reached invalid");
	return -1;
}

int
insert_mutation(char* seed, char* mutated_inp, int inp_len, int offset, int byte){
	int mutator = rand()2+1;
	
	switch(mutator){
		case 1:
			return insert_random_character(seed, mutated_inp, inp_len, offset, byte);
			break;
		case 2:
			return insert_known_integer(seed, mutated_inp, inp_len, offset, byte);
			break;
		default:
			perror("insert_mutation: out of bound");
			return inp_len;
	}
}

int
change_mutation(char* seed, char* mutated_inp, int inp_len, int offset, int byte){
	int mutator = rand()4+1;
	
	switch(mutator){
		case 1:
			return change_random_bits(seed, mutated_inp, inp_len, offset, byte);
			break;
		case 2:
			return change_random_bytes(seed, mutated_inp, inp_len, offset, byte);
			break;
		case 3:
			return change_simple_arith(seed, mutated_inp, inp_len, offset, byte);
			break;
		case 4:
			return change_known_integer(seed, mutated_inp, inp_len, offset, byte);
			break;
		default:
			perror("insert_mutation: out of bound");
			return inp_len;
	}
}

int 
delete_mutation(char* seed, char* mutated_inp, int inp_len, int offset, int byte){
	return delete_random_character(seed, mutated_inp, inp_len, offset, byte);
}

int
mutate(char* seed, char* mutated_inp, int inp_len){
	int len;
	int offset = rand()%inp_len;
	int mutate_mode = rand()%7+1;
	int byte = rand()%3+1;
	
	if(mutate_mode <= 2){
		len = insert_mutation(seed, mutated_inp, inp_len, offset, byte);	
	}
	else if(mutate_mode >= 3 && mutate_mode <= 6){
		len = change_mutation(seed, mutated_inp, inp_len, offset, byte);
	}
	else{
		len = delete_mutation(seed, mutated_inp, inp_len, offset, byte);
	}
	
	return len;
}
