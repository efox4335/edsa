#ifndef __edsa_htable__
#define __edsa_htable__
#include <stddef.h>
#include "edsa.h"

typedef struct{
	size_t ele_count;
	size_t data_size;
	size_t table_size;
	size_t load_val;
	void *htable;
}edsa_htable;

#endif
