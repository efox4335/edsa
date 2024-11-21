#include "edsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp_func(const void *const a, const void *const b)
{
	return *((int *) a) < *((int *) b);
}

void set_arr(size_t *arr, size_t size)
{
	for(size_t i = 0; i < size; ++i){
		arr[i] = i;
	}
}

//fisher yates
void scramble(size_t input[], size_t size)
{
	size_t swap_spot;
	size_t temp;

	srand(time(NULL));

	for(size_t i = 0; i < size - 1; ++i){
		swap_spot = (rand() % (size - i)) + i;

		temp = input[i];
		input[i] = input[swap_spot];
		input[swap_spot] = temp;
	}
}

//returns index of failed data
//returns size on pass
size_t check_arr(size_t *arr, size_t size)
{
	for(size_t i = 0; i < size; ++i){
		if(arr[i] != i){
			return i;
		}
	}

	return size;
}

//sets each element to an integer between size - 1 and 0
void rand_set_arr(size_t *arr, size_t size)
{
	srand(time(NULL));

	for(size_t i = 0; i < size; ++i){
		arr[i] = rand() % (size - 1);
	}
}

//returns second index of first unsorted pair
//returns size on pass
size_t check_sorted(size_t *arr, size_t size)
{
	for(size_t i = 1; i < size; ++i){
		if(arr[i - 1] > arr[i]){
			return i;
		}
	}

	return size;
}

int main(void)
{
	enum{DATA_AMOUNT = 1000};

	size_t ret_val = 0;
	char *fail_err = NULL;
	char *ret_str = NULL;
	edsa_heap *heap;
	size_t data[DATA_AMOUNT];

	edsa_heap_init(&heap, 1, sizeof (size_t), cmp_func);

	set_arr(data, DATA_AMOUNT);

	for(int i = 0; i < DATA_AMOUNT; ++i){
		edsa_heap_ins(heap, &(data[i]));
	}

	for(int i = 0; i < DATA_AMOUNT; ++i){
		edsa_heap_remove(heap, &(data[i]));
	}

	ret_val = check_arr(data, DATA_AMOUNT);

	if(ret_val != DATA_AMOUNT){
		printf("sorted data returned at index %ld not expected expected %ld instead got %ld\n",
		ret_val,
		ret_val,
		data[ret_val]);
		edsa_heap_free(heap);
		return 1;
	}

	edsa_heap_free(heap);



	edsa_heap_init(&heap, 1, sizeof (size_t), cmp_func);

	scramble(data, DATA_AMOUNT);

	for(int i = 0; i < DATA_AMOUNT; ++i){
		edsa_heap_ins(heap, &(data[i]));
	}

	for(int i = 0; i < DATA_AMOUNT; ++i){
		edsa_heap_remove(heap, &(data[i]));
	}

	ret_val = check_arr(data, DATA_AMOUNT);

	if(ret_val != DATA_AMOUNT){
		printf("scrambled data returned at index %ld not expected expected %ld instead got %ld\n",
		ret_val,
		ret_val,
		data[ret_val]);
		edsa_heap_free(heap);
		return 1;
	}

	edsa_heap_free(heap);



	edsa_heap_init(&heap, 1, sizeof (size_t), cmp_func);

	rand_set_arr(data, DATA_AMOUNT);

	for(int i = 0; i < DATA_AMOUNT; ++i){
		edsa_heap_ins(heap, &(data[i]));
	}

	for(int i = 0; i < DATA_AMOUNT; ++i){
		edsa_heap_remove(heap, &(data[i]));
	}

	ret_val = check_sorted(data, DATA_AMOUNT);

	if(ret_val != DATA_AMOUNT){
		printf("randomized data returned at index %ld not sorted got values %d and %d\n",
		ret_val,
		data[ret_val - 1],
		data[ret_val]);
		edsa_heap_free(heap);
		return 1;
	}

	edsa_heap_free(heap);

	return 0;
}
