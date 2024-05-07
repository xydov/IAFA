#include "rng.h"

#define MAX_RN 0x7FFFFFFF

const unsigned long long int rng_a = 0x5deece66d;
const unsigned long long int rng_c = 0xb;
const unsigned long long int rng_m = 0x1000000000000;

unsigned long long int next_val(unsigned long long int r_n) {
	return (rng_a * r_n + rng_c) % rng_m;
}

unsigned long int toss(unsigned short *seed) {
	unsigned long long int rn = seed[0] + ((unsigned long long int)seed[1] << 16) + ((unsigned long long int)seed[2] << 32);
	rn = next_val(rn);
	seed[0] = (unsigned short) (rn);
	seed[1] = (unsigned short) (rn>>16);
	seed[2] = (unsigned short) (rn>>32);
	return (rn >> 17) & MAX_RN;
}

RNG rng_initialize(unsigned long long int s){
	RNG rng;
	rng.xsubi[0] = (unsigned short) (s);
	rng.xsubi[1] = (unsigned short) (s>>16);
	rng.xsubi[2] = (unsigned short) (s>>32);
	return rng;
}

unsigned int rng_get_value(RNG *r, unsigned int max_value){
	unsigned int value;
	for (value = 0; toss(r->xsubi) < MAX_RN/2 && value < max_value; ++value);
	return value;
}
