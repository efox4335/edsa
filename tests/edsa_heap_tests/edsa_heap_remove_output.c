#include "edsa.h"
#include <stdio.h>

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

int main(void)
{
	enum{DATA_AMMOUNT = 1000};

	size_t ret_val = 0;
	char *fail_err = NULL;
	char *ret_str = NULL;
	edsa_heap *heap;
	size_t data[DATA_AMMOUNT];

	edsa_heap_init(&heap, 1, sizeof (size_t), cmp_func);

	set_arr(data, DATA_AMMOUNT);

	for(int i = 0; i < DATA_AMMOUNT; ++i){
		edsa_heap_ins(heap, &(data[i]));
	}

	for(int i = 0; i < DATA_AMMOUNT; ++i){
		edsa_heap_remove(heap, &(data[i]));
	}

	ret_val = check_arr(data, DATA_AMMOUNT);

	if(ret_val != DATA_AMMOUNT){
		printf("data returned at index %ld not expected expected %ld instead got %ld\n",\
		ret_val,
		ret_val,
		data[ret_val]);
		edsa_heap_free(heap);
		for(int i = 0; i < DATA_AMMOUNT; ++i){
			printf("%ld\n", data[i]);
		}
		return 1;
	}

	edsa_heap_free(heap);

	return 0;
}
