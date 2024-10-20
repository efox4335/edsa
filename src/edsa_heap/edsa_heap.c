/*
 - binary heap stored as an array
 - uses edsa_exparr to store the heap
 - cmp_func returns 1 when the element pointed to by first argument belongs above the second in the heap 0 otherwise
 - edsa_heap_build() should construct the heap bottom up
 - index of parent of node at pos is ((pos + 1) / 2) - 1
 - index of children of node at pos is ((pos + 1) * 2) - 1 and ((pos + 1) * 2)
*/
#include "edsa.h"
#include "edsa_heap.h"
#include <stddef.h>
#include <stdlib.h>

//return vals for static functions
//static functions that return error codes should only return these to avoid 2 errors having the same val
enum{
	SUCCESS,
	UP_HEAP_MALLOC_FAIL
};

static inline size_t get_parent_index(size_t index)
{
	return ((index + 1) >> 1) - 1;
}

static inline size_t get_left_child(size_t index)
{
	return ((index + 1) << 1) - 1;
}

static inline size_t get_right_child(size_t index)
{
	return (index + 1) << 1;
}

//moves node at index as far up in the heap as it can go
static size_t up_heap(edsa_heap *heap, size_t index)
{
	//no need to do anything if node at index is already root
	if(index == 0){
		return SUCCESS;
	}

	void *parent_ptr = NULL;
	void *ele_ptr = NULL;

	edsa_exparr_get_ele_ptr(heap->heap, index, (void **) &ele_ptr);
	edsa_exparr_get_ele_ptr(heap->heap, get_parent_index(index), (void **) &parent_ptr);

	//no need to continue if parent belongs higher then ele
	if((*(heap->cmp_func))(parent_ptr, ele_ptr)){
		return SUCCESS;
	}

	//stores node at index to avoid swaps
	void *ele_temp_store = malloc(heap->data_size);

	if(ele_temp_store == NULL){
		return UP_HEAP_MALLOC_FAIL;
	}

	edsa_exparr_read(heap->heap, index, ele_temp_store);

	size_t parent_index = get_parent_index(index);
	size_t child_index = index;
	do{
		edsa_exparr_ins(heap->heap, child_index, parent_ptr);

		child_index = parent_index;

		//if child is root
		if(child_index == 0){
			break;
		}

		parent_index = get_parent_index(child_index);

		edsa_exparr_get_ele_ptr(heap->heap, child_index, (void **) &ele_ptr);
		edsa_exparr_get_ele_ptr(heap->heap, parent_index, (void **) &parent_ptr);
	}while((*(heap->cmp_func))(ele_ptr, parent_ptr));

	edsa_exparr_ins(heap->heap, child_index, ele_temp_store);

	free(ele_temp_store);
	return SUCCESS;
}

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
