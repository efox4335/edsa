#include "edsa.h"
#include <stdio.h>
#include <stdlib.h>

enum{KEY_ARR_ELE = 4, DATA_ARR_ELE = 100};

typedef struct{
	size_t key_arr[4];
}key_type;

typedef struct{
	size_t data_arr[100];
}data_type;

void set_data_arr(data_type *arr, size_t size)
{
	for(size_t i = 0; i < size; ++i){
		for(size_t k = 0; k < DATA_ARR_ELE; ++k){
			(arr[i]).data_arr[k] = i;
		}
	}
}

void set_key_arr(key_type *arr, size_t size)
{
	for(size_t i = 0; i < size; ++i){
		for(size_t k = 0; k < KEY_ARR_ELE; ++k){
			(arr[i]).key_arr[k] = i;
		}
	}
}

//returns index of failed data
//returns size on pass
size_t check_data_arr(data_type *arr, size_t size)
{
	for(size_t i = 0; i < size; ++i){
		for(size_t k = 0; k < DATA_ARR_ELE; ++k){
			if((arr[i]).data_arr[k] != i){
				return i;
			}
		}
	}

	return size;
}

//returns index of failed key
//returns size on pass
size_t check_key_arr(key_type *arr, size_t size)
{
	for(size_t i = 0; i < size; ++i){
		for(size_t k = 0; k < KEY_ARR_ELE; ++k){
			if((arr[i]).key_arr[k] != i){
				return i;
			}
		}
	}

	return size;
}

//sets all elements of arr to -1
void reset_data_arr(data_type *arr, size_t size)
{
	for(size_t i = 0; i < size; ++i){
		for(size_t k = 0; k < DATA_ARR_ELE; ++k){
			(arr[i]).data_arr[k] = -1;
		}
	}
}

int main(void)
{
	enum{DATA_AMOUNT = 1000};

	size_t ret_val = 0;
	edsa_htable *htable;
	data_type data[DATA_AMOUNT];
	key_type key[DATA_AMOUNT];

	edsa_htable_init(&htable, sizeof(key_type), sizeof(data_type), 1);

	set_key_arr(key, DATA_AMOUNT);
	set_data_arr(data, DATA_AMOUNT);

	for(int i = 0; i < DATA_AMOUNT; ++i){
		edsa_htable_ins(htable, &(key[i]), &(data[i]));
	}

	reset_data_arr(data, DATA_AMOUNT);//set to make sure edsa_htable_read() outputs data

	for(int i = 0; i < DATA_AMOUNT; ++i){
		edsa_htable_read(htable, &(key[i]), &(data[i]));
	}


	ret_val = check_key_arr(key, DATA_AMOUNT);

	if(ret_val != DATA_AMOUNT){
		printf("edsa_htable_read_output.c: key at index %ld not expected expected %ld instead got %ld\n",
		ret_val,
		ret_val,
		key[ret_val].key_arr[0]);
		edsa_htable_free(htable);
		return 1;
	}

	ret_val = check_data_arr(data, DATA_AMOUNT);

	if(ret_val != DATA_AMOUNT){
		printf("edsa_htable_read_output.c: data returned at index %ld not expected expected %ld instead got %ld\n",
		ret_val,
		ret_val,
		data[ret_val].data_arr[0]);
		edsa_htable_free(htable);
		return 1;
	}

	edsa_htable_free(htable);

	return 0;
}
