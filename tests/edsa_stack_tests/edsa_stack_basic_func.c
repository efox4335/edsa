#include "../../src/edsa.h"
#include <stdio.h>

int main(void)
{
	edsa_stack *stack;
	int place_holder = 0xaaaaaaa;
	int ret_value;

	ret_value = edsa_stack_init(sizeof(int), 1, &stack);
	if(ret_value != EDSA_SUCCESS){
		edsa_print_error(stdout, ret_value);
		return 1;
	}

	ret_value = edsa_stack_push(stack, &place_holder);
	if(ret_value != EDSA_SUCCESS){
		edsa_print_error(stdout, ret_value);
		return 1;
	}

	ret_value = edsa_stack

	edsa_stack_free(stack);

	return !(ret_value == EDSA_SUCCESS);
}
