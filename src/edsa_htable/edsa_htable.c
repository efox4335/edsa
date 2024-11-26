/*
 - open addressing with quadratic probing function f(x) = x^2
 - hash table size is always prime so load factor can get up to .5
 - when .5 load factor is reached expand size to the next prime larger than twice the current size
*/
#include <stdlib.h>
#include <string.h>
#include "edsa_htable.h"

enum{
	EMPTY,//for slots that have never had an entry
	DELETED,//for slots that have had an entry but was sencince deleted
	FULL//for slots that have an entry
};

enum{//return codes for static functions
	SUCCESS,
	SLOT_USAGE_ARR_MARK_EMPTY_REALLOC_FAIL,
	SLOT_USAGE_ARR_MARK_EMPTY_INDEX_TOO_HIGH,
	INSERT_MALLOC_FAIL,
	EXPAND_TABLE_TABLE_TOO_LARGE,
	EXPAND_TABLE_MALLOC_FAIL,
	EXPAND_TABLE_REALLOC_FAIL,
	FIND_SLOT_MALLOC_FAIL
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

//sets index to the index of the slot with the associated key or if no slot is found htable->table_size
static size_t find_slot(edsa_htable *const restrict htable, void *const restrict key, size_t *index)
{
	size_t hash_temp = hash(key, htable->key_size);
	size_t probe_offset = 0;
	size_t temp_index = 0;
	char slot_state = 0;
	void *temp_slot_key = malloc(htable->key_size);

	if(temp_slot_key == NULL){
		return FIND_SLOT_MALLOC_FAIL;
	}

	hash_temp %= htable->table_size;//keeps from temp_index getting too big

	while(1){//no need for other break conditions as quadratic probing guarantees a slot will be found and if an empty slot is found no entry with that key is in the htable
		temp_index = (hash_temp + probe_offset * probe_offset) % (htable->table_size);//quadratic probe
		edsa_exparr_read(htable->slot_usage_arr, temp_index, &slot_state);

		if(slot_state == EMPTY){
			*index = htable->table_size;
			break;
		}else if(slot_state == FULL){
			edsa_exparr_read(htable->key_arr, temp_index, &temp_slot_key);

			if(!(memcmp(key, temp_slot_key, htable->key_size))){
				*index = temp_index;
				break;
			}
		}

		++probe_offset;
	}

	free(temp_slot_key);
	return SUCCESS;
}

//no need to check if the load factor is to big as edsa_htable_ins() will ensure it won't be to big
static size_t insert(edsa_htable *const restrict htable, void *const restrict key, void *const restrict data)
{
	size_t hash_temp = hash(key, htable->key_size);
	size_t probe_offset = 0;
	size_t ins_index = 0;
	char slot_state = 0;
	void *temp_slot_key = malloc(htable->key_size);

	if(temp_slot_key == NULL){
		return INSERT_MALLOC_FAIL;
	}

	hash_temp %= htable->table_size;//keeps from ins_index getting too big

	while(1){//no need for other break conditions as quadratic probing guarantees a slot will be found
		ins_index = (hash_temp + probe_offset * probe_offset) % (htable->table_size);//quadratic probe
		edsa_exparr_read(htable->slot_usage_arr, ins_index, &slot_state);

		if(slot_state != FULL){
			break;
		}

		edsa_exparr_read(htable->key_arr, ins_index, &temp_slot_key);

		if(!(memcmp(key, temp_slot_key, htable->key_size))){
			break;
		}

		++probe_offset;
	}

	slot_state = FULL;
	edsa_exparr_ins(htable->slot_usage_arr, ins_index, &slot_state);
	edsa_exparr_ins(htable->key_arr, ins_index, key);
	edsa_exparr_ins(htable->data_arr, ins_index, data);

	htable->full_slot_count += 1;

	free(temp_slot_key);
	return SUCCESS;
}

static size_t expand_table(edsa_htable *const restrict htable)
{
	void *temp_key = malloc(htable->key_size);
	if(temp_key == NULL){
		goto temp_key_expand_table_malloc_fail;
	}

	void *temp_data = malloc(htable->data_size);
	if(temp_data == NULL){
		goto temp_data_expand_table_malloc_fail;
	}

	if(0){
temp_data_expand_table_malloc_fail:
		free(temp_key);
temp_key_expand_table_malloc_fail:
		return EXPAND_TABLE_MALLOC_FAIL;
	}

	size_t new_size = htable->table_size;
	new_size <<= 1;
	new_size = next_largest_prime(new_size);

	if(new_size == 0){
		return EXPAND_TABLE_TABLE_TOO_LARGE;
	}

	size_t ret_val = 0;
	edsa_htable *temp_htable = NULL;
	ret_val = edsa_htable_init(&temp_htable, htable->key_size, htable->data_size, new_size);

	switch(ret_val){
		case EDSA_HTABLE_INIT_HTABLE_SIZE_TOO_LARGE:
			return EXPAND_TABLE_TABLE_TOO_LARGE;
		case EDSA_HTABLE_INIT_MALLOC_FAIL:
			return EXPAND_TABLE_MALLOC_FAIL;
		case EDSA_HTABLE_INIT_REALLOC_FAIL:
			return EXPAND_TABLE_REALLOC_FAIL;
		default:
			break;
	}

	char slot_state = 0;

	for(size_t i = 0; i < htable->table_size; ++i){
		edsa_exparr_read(htable->slot_usage_arr, i, &slot_state);

		if(slot_state == FULL){
			edsa_exparr_read(htable->key_arr, i, temp_key);
			edsa_exparr_read(htable->data_arr, i, temp_data);

			insert(temp_htable, temp_key, temp_data);
		}
	}

	//swaps the arrays with the new hash table with the arrays with the old hash table so edsa_htable_free() can free them along with temp_htable
	edsa_exparr *temp_arr;
	temp_arr = htable->slot_usage_arr;
	htable->slot_usage_arr = temp_htable->slot_usage_arr;
	temp_htable->slot_usage_arr = temp_arr;

	temp_arr = htable->key_arr;
	htable->key_arr = temp_htable->key_arr;
	temp_htable->key_arr = temp_arr;

	temp_arr = htable->data_arr;
	htable->data_arr = temp_htable->data_arr;
	temp_htable->data_arr = temp_arr;

	htable->full_slot_count = temp_htable->full_slot_count;
	htable->table_size = temp_htable->table_size;

	edsa_htable_free(temp_htable);
	return SUCCESS;
}

size_t edsa_htable_ins(edsa_htable *const restrict htable, void *const restrict key_in, void *const restrict data_in)
{
	size_t ret_val = 0;

	if(((htable->full_slot_count) << 1) >= htable->table_size){
		ret_val = expand_table(htable);

		switch(ret_val){
			case EXPAND_TABLE_MALLOC_FAIL:
				return EDSA_HTABLE_INS_MALLOC_FAIL;
			case EXPAND_TABLE_REALLOC_FAIL:
				return EDSA_HTABLE_INS_REALLOC_FAIL;
			case EXPAND_TABLE_TABLE_TOO_LARGE:
				return EDSA_HTABLE_INS_HTABLE_TOO_LARGE;
			default:
				break;
		}
	}

	ret_val = insert(htable, key_in, data_in);

	switch(ret_val){
		case INSERT_MALLOC_FAIL:
			return EDSA_HTABLE_INS_MALLOC_FAIL;
		default:
			break;
	}

	return EDSA_SUCCESS;
}

size_t edsa_htable_read(edsa_htable *const restrict htable, void *const restrict key_in, void *const restrict data_out)
{
	size_t ret_val = 0;
	size_t index = 0;

	ret_val = find_slot(htable, key_in, &index);

	switch(ret_val){
		case FIND_SLOT_MALLOC_FAIL:
			return EDSA_HTABLE_READ_MALLOC_FAIL;
		default:
			break;
	}

	if(index == htable->table_size){
		return EDSA_HTABLE_READ_NO_ENTRY;
	}

	edsa_exparr_read(htable->data_arr, index, data_out);

	return EDSA_SUCCESS;
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
