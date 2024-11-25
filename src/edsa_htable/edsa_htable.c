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

enum{//return codes for static functions
	SUCCESS,
	SLOT_USAGE_ARR_MARK_EMPTY_REALLOC_FAIL,
	SLOT_USAGE_ARR_MARK_EMPTY_INDEX_TOO_HIGH
};

static size_t slot_usage_arr_mark_empty(edsa_htable *const restrict htable)
{
	char EMPTY_VAL = EMPTY;
	size_t ret_val = 0;

	for(size_t i = 0; i < htable->table_size; ++i){
		ret_val = edsa_exparr_ins(htable->slot_usage_arr, i, &EMPTY_VAL);

		switch(ret_val){
			case EDSA_EXPARR_INS_INDEX_TO_HIGH:
				return SLOT_USAGE_ARR_MARK_EMPTY_INDEX_TOO_HIGH;
			case EDSA_EXPARR_INS_REALLOC_FAIL:
				return SLOT_USAGE_ARR_MARK_EMPTY_REALLOC_FAIL;
			case EDSA_SUCCESS:
				break;
		}
	}

	return SUCCESS;
}

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
//returns 0 on fail
static size_t next_largest_prime(size_t num)
{
	size_t pos_prime = num;
	size_t factor = 0;
	size_t quotient = 0;

	while(pos_prime < (size_t) -1){
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

	return 0;
}
