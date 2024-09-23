#include <stdlib.h>
#include "edsa_table.h"

//fnv-1a hash
static size_t hash(unsigned char *restrict key, const size_t len)
{
	size_t hash = 14695981039346656037LU;

	for(size_t i = 0; i < len; ++i){
		hash ^= key[i];
		hash *= 1099511628211;
	}

	return hash;
}

//todo add arr of large primes and improve alg
//todo check output matches list of primes
static size_t next_largest_prime(size_t num)
{
	size_t pos_prime = num;
	size_t factor = 0;
	size_t quotient = 0;

	while(1){
		factor = 1;
		quotient = 3;

		while((quotient > factor) && (pos_prime != quotient * factor)){
			++factor;
			quotient = pos_prime / factor;
		}

		if(pos_prime != quotient * factor){
			return pos_prime;
		}

		++pos_prime;
	}
}
