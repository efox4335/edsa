#include "../../src/edsa.h"
#include <stdio.h>
#include <stdlib.h>

void fill_arr(int *arr, int ele_num)
{
	for(int i = 0; i < ele_num; ++i){
		arr[i] = i;
	}
}

int main(void)
{
	enum{
		ARR_SIZE = 1000,
		TEST_AMMOUNT = 1000,
		DATA_RANGE = 20,
		DATA_SIZE = sizeof(int)
	};

	int *arr = NULL;
	int *temp = NULL;

	arr = malloc(ARR_SIZE * DATA_SIZE);

	if(arr == NULL){
		printf("edsa_stack_data_intgr.c: test data malloc failed");

		exit(1);
	}

	fill_arr(arr, ARR_SIZE);

	for(int i = 2; i <= DATA_RANGE; ++i){//runs each data size TEST_AMMOUNT times
		for(int j = 0; j < TEST_AMMOUNT; ++j){

		}

		temp = realloc(arr, ARR_SIZE * i * DATA_SIZE);//avoid orphaned arr pointer

		if(temp == NULL){
			printf("edsa_stack_data_intgr.c: test data realloc failed");

			exit(1);
		}

		arr = temp;

		fill_arr(arr, ARR_SIZE * i);
	}

	free(arr);

	return 0;
}
