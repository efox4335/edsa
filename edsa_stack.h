#ifndef __edsa_stack__
#define __edsa_stack__

#include <stddef.h>

typedef struct{
	size_t stack_size;

	void *elements;
}edsa_stack;
#endif
