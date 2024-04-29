#include <stdlib.h>
#include "edsa_stack.h"

//initializes stack returns NULL on error
edsa_stack *edsa_stack_init(size_t type_size, size_t element_number)
{
	size_t alloc_size = type_size * element_number;

	//returns null if no data to be allocated
	if(alloc_size == 0)
		return NULL;

	//returns null if multiplication overflows
	if(alloc_size / element_number != type_size)
		return NULL;

	void *temp_data = malloc(alloc_size);

	//if malloc fails
	if(temp_data == NULL)
		return NULL;

	edsa_stack *temp_stack_store = malloc(sizeof(edsa_stack));

	//if malloc fails
	if(temp_stack_store == NULL){
		free(temp_data);

		return NULL;
	}

	temp_stack_store->stack_place = 0;

	temp_stack_store->elements = temp_data;

	temp_stack_store->data_size = type_size;

	return temp_stack_store;
}

//returns number of elements in stack
size_t edsa_stack_size(edsa_stack *stack)
{
	return stack->stack_place + 1;
}
