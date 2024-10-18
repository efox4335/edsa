#ifndef __edsa_heap__
#define __edsa_heap__

#include <stddef.h>
#include "../edsa.h"

typedef struct{
	size_t size;
	size_t data_size;
	edsa_exparr *heap;
	int (*cmp_func)(const void *const, const void *const);
}edsa_heap;

size_t edsa_heap_init(edsa_heap *restrict *const restrict heap, const size_t heap_size, const size_t data_size, int (*cmp_func)(const void *const, const void *const));
size_t edsa_heap_free(edsa_heap *const restrict heap);
size_t edsa_heap_ins(edsa_heap *const restrict heap, void *const restrict data);
size_t edsa_heap_remove(edsa_heap *const restrict heap, void *const restrict data);
size_t edsa_heap_replace(edsa_heap *const restrict heap, void *const restrict data_in, void *const restrict data_out);
size_t edsa_heap_change_cmp_func(edsa_heap *const restrict heap, int (*cmp_func)(const void *const, const void *const));
size_t edsa_heap_build(edsa_heap *const restrict heap, void *const restrict arr);

#endif
