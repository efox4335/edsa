#include "../../src/edsa.h"
#include <stdio.h>

int main(void)
{
	edsa_stack *stack;
	char *fail_err = NULL;
	char *ret_str = NULL;

	int place_holder = 3;

	edsa_stack_init(sizeof(int), 1, &stack);

	edsa_stack_push(stack, &place_holder);

	int ret_value = edsa_stack_push(stack, &place_holder);

	if(ret_value != EDSA_STACK_PUSH_STACK_FULL){
		edsa_get_error_string(ret_value, &fail_err);
		edsa_get_error_string(EDSA_STACK_PUSH_STACK_FULL, &ret_str);
		printf("edsa_stack_overflow.c: edsa_stack_push failed to return %s instead returned %s\n",
		ret_str, fail_err);
		return 1;
	}

	edsa_stack_free(stack);

	return 0;
}
