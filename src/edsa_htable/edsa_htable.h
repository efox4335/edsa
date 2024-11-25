#ifndef __edsa_htable__
#define __edsa_htable__
#include <stddef.h>
#include "edsa.h"

typedef struct{
	size_t full_slot_count;
	size_t key_size;
	size_t data_size;
	size_t table_size;
	edsa_exparr *slot_usage_arr;
	edsa_exparr *key_arr;
	edsa_exparr *data_arr;
}edsa_htable;

size_t edsa_htable_init(edsa_htable *restrict *const restrict htable, const size_t key_size, const size_t data_size, const size_t htable_size);
size_t edsa_htable_free(edsa_htable *const restrict htable);
size_t edsa_htable_ins(edsa_htable *const restrict htable, void *const restrict key_in, void *const restrict data_in);
size_t edsa_htable_remove(edsa_htable *const restrict htable, void *const restrict key_in);
size_t edsa_htable_read(edsa_htable *const restrict htable, void *const restrict key_in, void *const restrict data_out);

#endif
