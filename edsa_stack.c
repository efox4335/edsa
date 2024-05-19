#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "edsa_stack.h"

//initializes stack returns NULL on error
edsa_stack *edsa_stack_init(size_t type_size, size_t element_number)
{
	size_t alloc_size = type_size * element_number;

	//returns null if no data to be allocated
	if(alloc_size == 0){
		fprintf(stderr, "edsa_stack_init: stack of zero size allocation attempted\n");
		return NULL;
	}

	//returns null if multiplication overflows
	if(alloc_size / element_number != type_size){
		fprintf(stderr, "edsa_stack_init: stack size multiplication overflowed\n");
		return NULL;
	}

	void *temp_data = malloc(alloc_size);

	//if malloc fails
	if(temp_data == NULL){
		fprintf(stderr, "edsa_stack_init: stack malloc failed\n");
		return NULL;
	}

	edsa_stack *temp_stack_store = malloc(sizeof(edsa_stack));

	//if malloc fails
	if(temp_stack_store == NULL){
		fprintf(stderr, "edsa_stack_init: stack data malloc failed\n");
		free(temp_data);

		return NULL;
	}

	temp_stack_store->stack_place = 0;

	temp_stack_store->elements = temp_data;

	temp_stack_store->data_size = type_size;

	temp_stack_store->stack_size = element_number;

	return temp_stack_store;
}

//adds element to stack without checking bounds
void edsa_stack_push_unsafe(edsa_stack *stack, void *element)
{
	memcpy(stack->elements + (stack->stack_place * stack->data_size), element, stack->data_size);

	return;
}

//adds element to stack with checking bounds
//retuns 1 on success
size_t edsa_stack_push_safe(edsa_stack *stack, void *element)
{
	if(edsa_stack_available_elements(stack) > 0){
		memcpy(stack->elements + (stack->stack_place * stack->data_size), element, stack->data_size);

		return 1;
	}

	fprintf(stderr, "edsa_stack_push_safe: attempted to push to stack without space\n");

	return 0;
}

//returns the number of elements that could be added with the current unused space
size_t edsa_stack_available_elements(edsa_stack *stack)
{
	return stack->stack_size - stack->stack_place;
}

//frees stack
void edsa_stack_free(edsa_stack *stack)
{
	free(stack->elements);
	free(stack);

	return;
}

//returns the size of the stack
size_t edsa_stack_size(edsa_stack *stack)
{
	return stack->stack_size;
}

//returns the number of elements currently on the stack
size_t edsa_stack_place(edsa_stack *stack)
{
	return stack->stack_place;
}
