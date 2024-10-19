/*
 - binary heap stored as an array
 - uses edsa_exparr to store the heap
 - cmp_func returns 1 when the element pointed to by first argument belongs above the second in the heap 0 otherwise
 - edsa_heap_build() should construct the heap bottom up
*/
#include "edsa.h"
#include "edsa_heap.h"
#include <stddef.h>
#include <stdlib.h>

size_t edsa_heap_init(edsa_heap *restrict *const restrict heap, const size_t heap_size, const size_t data_size, int (*cmp_func)(const void *const, const void *const))
{
	edsa_heap *temp_heap = (edsa_heap *) malloc(sizeof(edsa_heap));

	if(temp_heap == NULL){
		return EDSA_HEAP_INIT_MALLOC_FAILED;
	}

	edsa_exparr *temp_arr = NULL;
	size_t ret_val = edsa_exparr_init(&temp_arr, heap_size, data_size);

	//error checking already done by edsa_exparr_init()
	switch(ret_val){
		case EDSA_EXPARR_INTI_ZERO_ALLOC_SIZE:
			free(temp_heap);
			return EDSA_HEAP_INIT_ZERO_ALLOC_SIZE;
			break;
		case EDSA_EXPARR_INIT_MALLOC_FAILED:
			free(temp_heap);
			return EDSA_HEAP_INIT_MALLOC_FAILED;
			break;
		case EDSA_EXPARR_INIT_MULTIPLICATION_OVERFLOW:
			free(temp_heap);
			return EDSA_HEAP_INIT_MULTIPLICATION_OVERFLOW;
			break;
		case EDSA_SUCCESS:
			break;
	}

	temp_heap->cmp_func = cmp_func;
	temp_heap->heap = temp_arr;
	temp_heap->size = heap_size;
	temp_heap->data_size = data_size;

	*heap = temp_heap;

	return EDSA_SUCCESS;
}

size_t edsa_heap_free(edsa_heap *const restrict heap)
{
	edsa_exparr_free(heap->heap);
	free(heap);

	return EDSA_SUCCESS;
}
