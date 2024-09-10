#include "../../src/edsa.h"
#include <stdio.h>

int main(void)
{
	edsa_stack *stack;
	size_t place_holder = 0xaaaaaaa;
	int ret_value;
	char *fail_err = NULL;
	char *ret_str = NULL;

	ret_value = edsa_stack_init(sizeof(size_t), 1, &stack);
	if(ret_value != EDSA_SUCCESS){
		edsa_get_error_string(ret_value, &fail_err);
		edsa_get_error_string(EDSA_SUCCESS, &ret_str);
		printf("edsa_stack_basic_func.c: edsa_stack_init failed to return %s instead returned %s\n",
		ret_str, fail_err);
		return 1;
	}

	ret_value = edsa_stack_push(stack, &place_holder);
	if(ret_value != EDSA_SUCCESS){
		edsa_get_error_string(ret_value, &fail_err);
		edsa_get_error_string(EDSA_SUCCESS, &ret_str);
		printf("edsa_stack_basic_func.c: edsa_stack_push failed to return %s instead returned %s\n",
		ret_str, fail_err);
		return 1;
	}

	ret_value = edsa_stack_pop(stack, &place_holder);
	if(ret_value != EDSA_SUCCESS){
		edsa_get_error_string(ret_value, &fail_err);
		edsa_get_error_string(EDSA_SUCCESS, &ret_str);
		printf("edsa_stack_basic_func.c: edsa_stack_pop failed to return %s instead returned %s\n",
		ret_str, fail_err);
		return 1;
	}

	ret_value = edsa_stack_available_elements(stack, &place_holder);
	if(ret_value != EDSA_SUCCESS){
		edsa_get_error_string(ret_value, &fail_err);
		edsa_get_error_string(EDSA_SUCCESS, &ret_str);
		printf("edsa_stack_basic_func.c: edsa_stack_available_elements failed to return %s instead returned %s\n",
		ret_str, fail_err);
		return 1;
	}

	ret_value = edsa_stack_size(stack, &place_holder);
	if(ret_value != EDSA_SUCCESS){
		edsa_get_error_string(ret_value, &fail_err);
		edsa_get_error_string(EDSA_SUCCESS, &ret_str);
		printf("edsa_stack_basic_func.c: edsa_stack_size failed to return %s instead returned %s\n",
		ret_str, fail_err);
		return 1;
	}

	ret_value = edsa_stack_place(stack, &place_holder);
	if(ret_value != EDSA_SUCCESS){
		edsa_get_error_string(ret_value, &fail_err);
		edsa_get_error_string(EDSA_SUCCESS, &ret_str);
		printf("edsa_stack_basic_func.c: edsa_stack_place failed to return %s instead returned %s\n",
		ret_str, fail_err);
		return 1;
	}

	ret_value = edsa_stack_realloc(stack, 7);
	if(ret_value != EDSA_SUCCESS){
		edsa_get_error_string(ret_value, &fail_err);
		edsa_get_error_string(EDSA_SUCCESS, &ret_str);
		printf("edsa_stack_basic_func.c: edsa_stack_realloc failed to return %s instead returned %s\n",
		ret_str, fail_err);
		return 1;
	}

	ret_value = edsa_stack_free(stack);
	if(ret_value != EDSA_SUCCESS){
		edsa_get_error_string(ret_value, &fail_err);
		edsa_get_error_string(EDSA_SUCCESS, &ret_str);
		printf("edsa_stack_basic_func.c: edsa_stack_free failed to return %s instead returned %s\n",
		ret_str, fail_err);
		return 1;
	}

	return 0;
}
