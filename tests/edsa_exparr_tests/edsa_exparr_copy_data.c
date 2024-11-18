/*
 - sets part of the array copys that to another part and checks that both parts match the original
*/
#include "edsa.h"
#include <stdio.h>

int main(void)
{
	edsa_exparr *arr;
	size_t test_size = 500;
	int temp = 0;

	edsa_exparr_init(&arr, 1, sizeof(int));

	for(int i = 0; (size_t) i < test_size; ++i){//sets original segment
		edsa_exparr_ins(arr, i, &i);
	}

	for(int i = 0; (size_t) i < test_size; ++i){//sets copied segment
		edsa_exparr_copy(arr, i, i + test_size);
	}

	for(int i = 0; (size_t) i < test_size; ++i){//checks original segment
		edsa_exparr_read(arr, i, &temp);
		if(i != temp){
			printf("edsa_exparr_copy_data.c: data in original segment at index %d does not match inputed data should be %d instead was %d\n",
			i, i, temp);

			fflush(stdout);

			return 1;
		}
	}

	for(int i = 0; (size_t) i < test_size; ++i){//checks original segment
		edsa_exparr_read(arr, i + test_size, &temp);
		if(i != temp){
			printf("edsa_exparr_copy_data.c: data in copied segment at index %d does not match inputed data should be %d instead was %d\n",
			i, i, temp);

			fflush(stdout);

			return 1;
		}
	}

	edsa_exparr_free(arr);

	return 0;
}
