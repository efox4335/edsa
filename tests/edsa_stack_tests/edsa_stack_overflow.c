#include "../../src/edsa.h"

int main(void)
{
	edsa_stack *stack;

	int place_holder = 3;

	edsa_stack_init(sizeof(int), 1, &stack);

	edsa_stack_push(stack, &place_holder);

	int ret_value = edsa_stack_push(stack, &place_holder);

	edsa_stack_free(stack);

	return !(ret_value == EDSA_STACK_PUSH_STACK_FULL);
}
