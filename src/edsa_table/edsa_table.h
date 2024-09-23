#ifndef __edsa_hash_table__
#define __edsa_hash_table__

typedef struct{
	size_t ele_count;
	size_t data_size;
	size_t table_size;
	size_t load_val;
	void *table;
}edsa_table;

#endif
