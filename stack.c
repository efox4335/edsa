#include <stdlib.h>
#include "stack.h"

edsa_stack *edsa_stack_init(size_t type_size, size_t element_number)
{
	size_t alloc_size = type_size * element_number;

	//returns null if no data to be allocated
	if(alloc_size == 0)
		return NULL;

	//returns null if multiplication overflows
	if(alloc_size / element_number != type_size)
		return NULL;

	void *stack = malloc(alloc_size);

	//if malloc fails
	if(stack == NULL)
		return NULL;


}
