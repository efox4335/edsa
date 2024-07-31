#include "../../src/edsa.h"

int main(void)
{
	edsa_stack *stack;

	int place_holder;

	edsa_stack_init(sizeof(int), 1, &stack);

	int ret_value = edsa_stack_pop(stack, &place_holder);

	edsa_stack_free(stack);

	return !(ret_value == EDSA_STACK_POP_STACK_EMPTY);
}
