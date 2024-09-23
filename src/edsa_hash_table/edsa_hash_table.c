//fnv-1a hash
static unsigned long hash(unsigned char *restrict key, const int len)
{
	unsigned long hash = 14695981039346656037LU;

	for(int i = 0; i < len; ++i){
		hash ^= key[i];
		hash *= 1099511628211;
	}

	return hash;
}
