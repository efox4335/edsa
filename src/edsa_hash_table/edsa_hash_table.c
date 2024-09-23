#include <stdlib.h>

//fnv-1a hash
static size_t hash(unsigned char *restrict key, const size_t len)
{
	size_t hash = 14695981039346656037LU;

	for(size_t i = 0; i < len; ++i){
		hash ^= key[i];
		hash *= 1099511628211;
	}

	return hash;
}
