#include "../include/mutating.h"

static int8_t interesting_8[] = { INTERESTING_8 };
static int16_t interesting_16[] = { INTERESTING_8, INTERESTING_16 };
static int32_t interesting_32[] = { INTERESTING_8, INTERESTING_16, INTERESTING_32 };int

delete_random_character(char* seed, char* mutated_inp, int length){
	if(length < 1) {
		perror("delete_random_character: length error");
		return length;
	}

	int pos;
	pos = rand()%length; // 0 ~ seedlen(seed)

	memcpy(mutated_inp, seed, length);
	mutated_inp[pos] = 127;

	return length-1;
}

int
insert_random_character(char* seed, char* mutated_inp, int length){
	int pos;
	pos = rand()%length; // 0 ~ seedlen(seed)

	char rand_char = rand()%95 + 32; // 32 ~ 127

	memcpy(mutated_inp, seed, sizeof(char) * length);

	mutated_inp[pos] = rand_char;

	for(int i=pos+1; i<length+1; i++){
		mutated_inp[i] = seed[i-1];
	}

	return length+1;
}

int
flip_random_character(char* seed, char* mutated_inp, int length){
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
	if(length < 1){
		memcpy(mutated_inp, seed, sizeof(char) * length);
		return length;
	}

	int pos;
	pos = rand()%length;

	int bytes = rand()%3+1;

	if(bytes == 3 && (length-pos) >= 4){
		unsigned int bit = 255;

		memcpy(mutated_inp, seed, length);

		for(int i=0; i<4; i++){
			char c = seed[pos + i];
			char new_c = c ^ bit;
			mutated_inp[pos + i] = new_c;
		}

		return length;
	}
	else if(bytes == 2 && (length-pos) >= 2){
		unsigned int bit = 255;

		memcpy(mutated_inp, seed, length);

		for(int i=0; i<2; i++){
			char c = seed[pos + i];
			char new_c = c ^ bit;
			mutated_inp[pos + i] = new_c;
		}

		return length;
	}
	else{
		unsigned int bit = 255;

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
known_integers(char* seed, char* mutated_inp, int length){
	if(length < 1){
		memcpy(mutated_inp, seed, sizeof(char) * length);
		return length;
	}

	int pos = rand()%length;

	int bytes = rand()%3+1;

	if(bytes == 3 && (length-pos) >= 4){

		memcpy(mutated_inp, seed, length);

		*(uint32_t*)(mutated_inp + pos) = interesting_32[rand()%27];

		return length;
	}
	else if(bytes == 2 && (length-pos) >= 2){

		memcpy(mutated_inp, seed, length);

		*(uint16_t*)(mutated_inp + pos) = interesting_16[rand()%19];

		return length;
	}
	else{

		memcpy(mutated_inp, seed, length);

		*(uint8_t*)(mutated_inp + pos) = interesting_8[rand()%9];

		return length;
	}


	perror("known_integers: reached invalid");
	return -1;
}

int
mutate(char* seed, char* mutated_inp, int inp_len){
	int mutators = rand()%7+1;
	int len;
	if(mutators == 1){
		len = delete_random_character(seed, mutated_inp, inp_len);
	}
	else if(mutators == 2){
		len = insert_random_character(seed, mutated_inp, inp_len);
	}
	else if(mutators == 3){
		len = flip_random_character(seed, mutated_inp, inp_len);
	}
	else if(mutators == 4){
		len = flip_two_bits(seed, mutated_inp, inp_len);
	}
	else if(mutators == 5){
		len = flip_on_bytes(seed, mutated_inp, inp_len);
	}
	else if(mutators == 6){
		len = simple_arithmetics(seed, mutated_inp, inp_len);
	}
	else{
		len = known_integers(seed, mutated_inp, inp_len);
	}
	return len;
}
