#include "../../src/edsa.h"
#include <stdlib.h>
#include <time.h>


int main(void)
{
	edsa_stack *stack;

	srand(time(NULL));

	int element = rand();

	edsa_stack_init(sizeof(int), 1, &stack);

	edsa_stack_push(stack, &element);

	int check;

	edsa_stack_pop(stack, &check);

	edsa_stack_free(stack);

	return !(check == element);
}
