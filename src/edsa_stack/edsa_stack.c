#include <stdlib.h>
#include <string.h>
#include "edsa_stack.h"
#include "../edsa_error_codes/edsa_error_codes.h"

static size_t get_data_size(const edsa_stack *const restrict stack);
static void *current_place_address(const edsa_stack *const restrict stack);
static void *next_place_address(const edsa_stack *const restrict stack);
static void *get_stack_pointer(const edsa_stack *const restrict stack);

//returns the address of the top of the stack
static void *current_place_address(const edsa_stack *const restrict stack)
{
	return (char *) get_stack_pointer(stack) + ((stack->stack_place - 1) * get_data_size(stack));
}

//returns the address of the empty space above the top of the stack
static void *next_place_address(const edsa_stack *const stack)
{
	return  (char *) get_stack_pointer(stack) + (stack->stack_place * get_data_size(stack));
}

//returns the size of the data type on the stack
static size_t get_data_size(const edsa_stack *const stack)
{
	return stack->data_size;
}

//returns base pointer to stack
static void *get_stack_pointer(const edsa_stack *const stack)
{
	return stack->elements;
}

//initializes stack returns NULL on error
size_t edsa_stack_init(const size_t type_size, const size_t element_number, edsa_stack **const restrict stack)
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

	return EDSA_SUCCESS;
}

//pops value from the top of the stack with checking if the stack is empty
size_t edsa_stack_pop(edsa_stack *const restrict stack, void *const restrict element)
{
	size_t stack_place;

	edsa_stack_place(stack, &stack_place);

	if(stack_place > 0){
		memcpy(element, current_place_address(stack), get_data_size(stack));

		stack->stack_place -= 1;

		return EDSA_SUCCESS;
	}

	return EDSA_STACK_POP_STACK_EMPTY;
}

//adds element to stack with checking bounds
size_t edsa_stack_push(edsa_stack *const restrict stack, void *const restrict element)
{
	size_t elements_left;

	edsa_stack_available_elements(stack, &elements_left);

	if(elements_left > 0){
		memcpy(next_place_address(stack), element, get_data_size(stack));

		stack->stack_place += 1;

		return EDSA_SUCCESS;
	}

	return EDSA_STACK_PUSH_STACK_FULL;
}

//returns the number of elements that could be added with the current unused space
size_t edsa_stack_available_elements(edsa_stack *const restrict stack, size_t *const restrict value)
{
	*value = stack->stack_size - stack->stack_place;

	return EDSA_SUCCESS;
}

//frees stack
size_t edsa_stack_free(edsa_stack *const restrict stack)
{
	free(get_stack_pointer(stack));
	free(stack);

	return EDSA_SUCCESS;
}

//returns the size of the stack
size_t edsa_stack_size(edsa_stack *const restrict stack, size_t *const restrict value)
{
	*value = stack->stack_size;

	return EDSA_SUCCESS;
}

//returns the number of elements currently on the stack
size_t edsa_stack_place(edsa_stack *const restrict stack, size_t *const restrict value)
{
	*value = stack->stack_place;

	return EDSA_SUCCESS;
}

//resizes stack
size_t edsa_stack_realloc(edsa_stack *const restrict stack, const size_t new_size)
{
	void *temp;

	temp = realloc(stack->elements, get_data_size(stack) * new_size);

	if(temp == NULL){
		return EDSA_STACK_REALLOC_FAILED;
	}

	stack->elements = temp;

	stack->stack_size = new_size;

	return EDSA_SUCCESS;
}
