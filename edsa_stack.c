#include <stdlib.h>
#include <string.h>
#include "edsa_stack.h"

//initializes stack returns NULL on error
size_t edsa_stack_init(size_t type_size, size_t element_number, edsa_stack **stack)
{
	size_t alloc_size = type_size * element_number;

	//returns null if no data to be allocated
	if(alloc_size == 0){
		return EDSA_STACK_INIT_ZERO_ALLOC_SIZE;
	}

	//returns null if multiplication overflows
	if(alloc_size / element_number != type_size){
		return EDSA_STACK_INIT_STACK_SIZE_MULTIPLICATION_OVERFLOW;
	}

	void *temp_data = malloc(alloc_size);

	//if malloc fails
	if(temp_data == NULL){
		return EDSA_STACK_INIT_STACK_MALLOC_FAILED;
	}

	edsa_stack *temp_stack_store = malloc(sizeof(edsa_stack));

	//if malloc fails
	if(temp_stack_store == NULL){
		free(temp_data);

		return EDSA_STACK_INIT_STACK_METADATA_MALLOC_FAILED;
	}

	temp_stack_store->stack_place = 0;

	temp_stack_store->elements = temp_data;

	temp_stack_store->data_size = type_size;

	temp_stack_store->stack_size = element_number;

	*stack = temp_stack_store;

	return EDSA_STACK_SUCCESS;
}

//pops value from the top of the stack without checking if the stack is empty
size_t edsa_stack_pop_unsafe(edsa_stack *stack, void *element)
{
	memcpy(element, stack->elements + (stack->stack_place * stack->data_size), stack->data_size);

	stack->stack_place -= 1;

	return EDSA_STACK_SUCCESS;
}

//pops value from the top of the stack without checking if the stack is empty
size_t edsa_stack_pop_safe(edsa_stack *stack, void *element)
{
	size_t stack_place;

	edsa_stack_place(stack, &stack_place);

	if(stack_place > 0){
		memcpy(element, stack->elements + (stack->stack_place * stack->data_size), stack->data_size);

		stack->stack_place -= 1;

		return EDSA_STACK_SUCCESS;
	}

	return EDSA_STACK_POP_SAFE_STACK_EMPTY;
}

//adds element to stack without checking bounds
size_t edsa_stack_push_unsafe(edsa_stack *stack, void *element)
{
	memcpy(stack->elements + (stack->stack_place * stack->data_size), element, stack->data_size);

	stack->stack_place += 1;

	return EDSA_STACK_SUCCESS;
}

//adds element to stack with checking bounds
size_t edsa_stack_push_safe(edsa_stack *stack, void *element)
{
	size_t elements_left;

	edsa_stack_available_elements(stack, &elements_left);

	if(elements_left > 0){
		memcpy(stack->elements + (stack->stack_place * stack->data_size), element, stack->data_size);

		stack->stack_place += 1;

		return EDSA_STACK_SUCCESS;
	}

	return EDSA_STACK_PUSH_SAFE_STACK_FULL;
}

//returns the number of elements that could be added with the current unused space
size_t edsa_stack_available_elements(edsa_stack *stack, size_t *value)
{
	*value = stack->stack_size - stack->stack_place;

	return EDSA_STACK_SUCCESS;
}

//frees stack
size_t edsa_stack_free(edsa_stack *stack)
{
	free(stack->elements);
	free(stack);

	return EDSA_STACK_SUCCESS;
}

//returns the size of the stack
size_t edsa_stack_size(edsa_stack *stack, size_t *value)
{
	*value = stack->stack_size;

	return EDSA_STACK_SUCCESS;
}

//returns the number of elements currently on the stack
size_t edsa_stack_place(edsa_stack *stack, size_t *value)
{
	*value = stack->stack_place;

	return EDSA_STACK_SUCCESS;
}
