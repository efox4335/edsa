#ifndef __edsa_exparr__
#define __edsa_exparr__

#include <stddef.h>

typedef struct{
	size_t arr_size;
	size_t data_size;
	void *restrict arr;
}edsa_exparr;

size_t edsa_exparr_init(edsa_exparr *restrict *const restrict arr, const size_t arr_size, const size_t data_size);
size_t edsa_exparr_free(edsa_exparr *const restrict arr);
size_t edsa_exparr_ins(edsa_exparr *const restrict arr, size_t index, void *const restrict data);
size_t edsa_exparr_read(edsa_exparr *const restrict arr, size_t index, void *const restrict data);
size_t edsa_exparr_batch_ins(edsa_exparr *const restrict arr, size_t index, void *const restrict data, size_t amount);
size_t edsa_exparr_copy(edsa_exparr *const restrict arr, size_t src_index, size_t dest_index);
size_t edsa_exparr_swap(edsa_exparr *const restrict arr, size_t fst_index, size_t snd_index);
size_t edsa_exparr_sort_segment(edsa_exparr *const restrict arr, int (*cmp_func)(const void *, const void *), const size_t st_index, const size_t end_index);

#endif
