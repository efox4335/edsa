#ifndef __edsa_htable__
#define __edsa_htable__
#include <stddef.h>
#include "edsa.h"

typedef struct{
	size_t ele_count;
	size_t key_size;
	size_t data_size;
	size_t table_size;
	edsa_exparr *key_arr;
	edsa_exparr *data_arr;
}edsa_htable;

#endif
