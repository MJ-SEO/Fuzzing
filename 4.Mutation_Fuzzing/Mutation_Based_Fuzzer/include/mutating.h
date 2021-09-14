#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>


#define INTERESTING_8   \
	-1,            /*                                         */ \
        0,            /*                                         */ \
        1,            /*                                         */ \
        16,           /* One-off with common buffer size         */ \
        32,           /* One-off with common buffer size         */ \
        64,           /* One-off with common buffer size         */ \
        100,          /* One-off with common buffer size         */ \
        127           /* Overflow signed 8-bit when incremented  */

#define INTERESTING_16 \
        -32768,        /* Overflow signed 16-bit when decremented */\
        -129,          /* Overflow signed 8-bit                   */ \
        128,          /* Overflow signed 8-bit                   */ \
        255,          /* Overflow unsig 8-bit when incremented   */ \
        256,          /* Overflow unsig 8-bit                    */ \
        512,          /* One-off with common buffer size         */ \
        1000,         /* One-off with common buffer size         */ \
        1024,         /* One-off with common buffer size         */ \
        4096,         /* One-off with common buffer size         */ \
        32767         /* Overflow signed 16-bit when incremented */

#define INTERESTING_32 \
        -2147483648LL, /* Overflow signed 32-bit when decremented */ \
        -100663046,    /* Large negative number (endian-agnostic) */ \
        -32769,        /* Overflow signed 16-bit                  */ \
        32768,        /* Overflow signed 16-bit                  */ \
        65535,        /* Overflow unsig 16-bit when incremented  */ \
        65536,        /* Overflow unsig 16 bit                   */ \
        100663045,    /* Large positive number (endian-agnostic) */ \
        2147483647    /* Overflow signed 32-bit when incremented */

int delete_random_character(char* seed, char* mutated_inp, int length);

int insert_random_character(char* seed, char* mutated_inp, int length);

int flip_random_character(char* seed, char* mutated_inp, int length);

int flip_two_bits(char* seed, char* mutated_inp, int length);

int flip_on_bytes(char* seed, char* mutated_inp, int length);

int simple_arithmetics(char* seed, char* mutated_inp, int length);

int known_integers(char* seed, char* mutated_inp, int length);

int mutate(char* seed, char* mutated_inp, int length);
