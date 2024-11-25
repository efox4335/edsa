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
		quotient = 0;

		do{
			++factor;
			quotient = pos_prime / factor;
		}while((quotient > factor) && (pos_prime != quotient * factor));

		if(pos_prime != quotient * factor){
			return pos_prime;
		}

		++pos_prime;
	}

	return 0;
}

size_t edsa_htable_init(edsa_htable *restrict *const restrict htable, const size_t key_size, const size_t data_size, const size_t htable_size)
{
	if(htable_size == 0){
		return EDSA_HTABLE_INIT_HTABLE_SIZE_ZERO;
	}

	size_t htable_size_temp = next_largest_prime(htable_size);

	if(htable_size_temp == 0){
		return EDSA_HTABLE_INIT_HTABLE_SIZE_TOO_LARGE;
	}

	size_t ret_val = 0;

	edsa_exparr *slot_usage_arr_temp = NULL;
	ret_val = edsa_exparr_init(&slot_usage_arr_temp, htable_size_temp, sizeof(char));
	if(ret_val != EDSA_SUCCESS){
		goto edsa_exparr_init_error;
	}

	edsa_exparr *key_arr_temp = NULL;
	ret_val = edsa_exparr_init(&key_arr_temp, htable_size_temp, key_size);
	if(ret_val != EDSA_SUCCESS){
		goto edsa_exparr_init_error;
	}

	edsa_exparr *data_arr_temp = NULL;
	ret_val = edsa_exparr_init(&data_arr_temp, htable_size_temp, data_size);
	if(ret_val != EDSA_SUCCESS){
		goto edsa_exparr_init_error;
	}

	if(0){//edsa_exparr_init error cleanup
edsa_exparr_init_error:
		switch(ret_val){
			case EDSA_EXPARR_INIT_MALLOC_FAILED:
				return EDSA_HTABLE_INIT_MALLOC_FAIL;
			case EDSA_EXPARR_INIT_MULTIPLICATION_OVERFLOW:
				return EDSA_HTABLE_INIT_HTABLE_SIZE_TOO_LARGE;
			case EDSA_EXPARR_INIT_ZERO_ALLOC_SIZE:
				return EDSA_HTABLE_INIT_HTABLE_SIZE_ZERO;
		}
	}

	edsa_htable *htable_temp = malloc(sizeof(edsa_htable));
	if(htable_temp == NULL){
		return EDSA_HTABLE_INIT_MALLOC_FAIL;
	}

	htable_temp->data_arr = data_arr_temp;
	htable_temp->data_size = data_size;
	htable_temp->full_slot_count = 0;
	htable_temp->key_arr = key_arr_temp;
	htable_temp->key_size = key_size;
	htable_temp->slot_usage_arr = slot_usage_arr_temp;
	htable_temp->table_size = htable_size_temp;


	switch(slot_usage_arr_mark_empty(htable_temp)){
		case SLOT_USAGE_ARR_MARK_EMPTY_INDEX_TOO_HIGH:
			ret_val = EDSA_HTABLE_INIT_HTABLE_SIZE_TOO_LARGE;
			goto slot_usage_arr_mark_empty_error;
		case SLOT_USAGE_ARR_MARK_EMPTY_REALLOC_FAIL:
			ret_val = EDSA_HTABLE_INIT_REALLOC_FAIL;
			goto slot_usage_arr_mark_empty_error;
		default:
			break;
	}

	if(0){//if slot_usage_arr_mark_empty returns error it shouldn't as all cases should be covered by edsa_exparr_init()
slot_usage_arr_mark_empty_error:
		edsa_exparr_free(key_arr_temp);
		edsa_exparr_free(data_arr_temp);
		edsa_exparr_free(slot_usage_arr_temp);

		free(htable_temp);

		return ret_val;
	}

	*htable = htable_temp;

	return EDSA_SUCCESS;
}

size_t edsa_htable_free(edsa_htable *const restrict htable)
{
	edsa_exparr_free(htable->data_arr);
	edsa_exparr_free(htable->key_arr);
	edsa_exparr_free(htable->slot_usage_arr);

	free(htable);

	return EDSA_SUCCESS;
}
