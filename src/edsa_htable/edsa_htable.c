/*
 - open addressing with quadratic probing function f(x) = x^2
 - hash table size is always prime so load factor can get up to .5
 - when .5 load factor is reached expand size to the next prime larger than twice the current size
*/
#include <stdlib.h>
#include "edsa_htable.h"

enum{
	EMPTY,//for slots that have never had an entry
	DELETED,//for slots that have had an entry but was sencince deleted
	FULL//for slots that have an entry
};

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
