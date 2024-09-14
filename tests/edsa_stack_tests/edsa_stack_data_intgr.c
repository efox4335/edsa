#include "../../src/edsa.h"
#include <stdio.h>
#include <stdlib.h>

void fill_arr(unsigned char *arr, int ele_num)
{
	for(int i = 0; i < ele_num; ++i){
		arr[i] = i;
	}
}

//returns 1 on fail
int chk_data(unsigned char *arr, int ele_num)
{
	for(int i = 0; i < ele_num; ++i){
		if(arr[i] != (unsigned char) i){
			return 1;
		}
	}

	return 0;
}

int main(void)
{
	enum{
		ARR_SIZE = 1000,
		TEST_AMMOUNT = 1000,
		DATA_RANGE = 20,
		DATA_SIZE = sizeof(unsigned char)//unsigned char because signed char casts are implementation defined
	};

	unsigned char *arr = NULL;

	arr = malloc(ARR_SIZE * DATA_SIZE * DATA_RANGE);

	if(arr == NULL){
		printf("edsa_stack_data_intgr.c: test data malloc failed");

		return 1;
	}

	fill_arr(arr, ARR_SIZE * DATA_RANGE);

	for(int i = 1; i <= DATA_RANGE; ++i){//runs each data size TEST_AMMOUNT times
		for(int j = 0; j < TEST_AMMOUNT; ++j){

		}
	}

	free(arr);

	return 0;
}
