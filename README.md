# Edsa Readme
A data structures and algorithms library written in c. Should not be used to store sensitive information.
## Supported data structures/algorithms
| Data structure/Algorithm | Description |
| --- | --- |
| exparr | An array that expands to fit new elements added. Supports arbitrary typed and sized data. |
| heap | A heap with a user supplied compare function. Expands to fit arbitrary typed and sized data. |
## Build and Installation Instructions
### Linux
From the root of the project directory run this command.

```cmake -S . --preset=release && cmake --build --preset=release```
### Windows
Untested.
### Macos
Untested.

## Usage
Must include `edsa.h` in `src/` directory. Must link aginst either `libedsa_shared.so` or `libedsa_static.a` from `builds/` directory. Should not be used to store sensitive information.

## exparr
To use exparr a vairable of type `edsa_exparr *` will need to be created.

### `edsa_exparr_init(edsa_exparr **arr, size_t arr_size, size_t data_size)`
Initalizes exparr `arr` with size `arr_size` and data size `data_size`.

Arguments:
 - First argument the address of the `edsa_exparr *` vairable.
   - Must not have been previously initialized by `edsa_exparr_init()` without having been freed by `edsa_exparr_free()`.
 - Second argument the amount of elements to be allocated.
   - Must be greater then 0.
 - Third argument the size of the data type given by `sizeof()`.

Return values:
 - `EDSA_SUCCESS`
   - Returns upon successful run.
 - `EDSA_EXPARR_INTI_ZERO_ALLOC_SIZE`
   - Returns when `arr_size * data_size` equals 0.
   - Does not need to be freed.
 - `EDSA_EXPARR_INIT_MULTIPLICATION_OVERFLOW`
   - Returns when `arr_size * data_size` overflows.
   - Does not need to be freed.
 - `EDSA_EXPARR_INIT_MALLOC_FAILED`
   - Returns when `malloc()` fails during run.
   - Does not need to be freed.

#### Example
```c
size_t error_val;
edsa_exparr *arr;

error_val = edsa_exparr_init(&arr, 10, sizeof(char));
```

### `edsa_exparr_free(edsa_exparr *arr)`
Frees exparr `arr`.

Argumens:
 - First argument a pointer of type `edsa_exparr *`.
   - Must have been previously initialized by `edsa_exparr_init()` without having been freed by `edsa_exparr_free()`.

Return values:
 - `EDSA_SUCCESS`
   - Returns upon successful run.

#### Example
```c
size_t error_val;
edsa_exparr *arr;

...

error_val = edsa_exparr_free(arr);
```

### `edsa_exparr_ins(edsa_exparr *arr, size_t index, void *data)`
Inserts data `*data` into exparr `arr` at index `index`.

Arguments:
 - First argument a pointer of type `edsa_exparr *`.
   - Must have been previously initialized by `edsa_exparr_init()` without having been freed by `edsa_exparr_free()`.
 - Second argument an index at which the data will be put.
   - Array will expand in size if index is outside of array.
 - Third argument a pointer to the data to be inserted.
   - Data must be the same size as supplied to `edsa_exparr_init()`.


Return values:
 - `EDSA_SUCCESS`
   - Returns upon successful run.
 - `EDSA_EXPARR_INS_INDEX_TO_HIGH`
   - Returns if the index is to high for the array size to be stored.
 - `EDSA_EXPARR_INS_REALLOC_FAIL`
   - Returns if `realloc()` fails on the array.
   - Still needs to be freed by `edsa_exparr_free()`.

#### Example
```c
size_t error_val;
edsa_exparr *arr;
char c = 'c';

...

error_val = edsa_exparr_ins(arr, 1, &c);
```

### `edsa_exparr_copy(edsa_exparr *arr, size_t src_index, size_t dest_index)`
Copies the data at index `src_index` to index `dest_index` in exparr `arr`.

Arguments:
 - First argument a pointer of type `edsa_exparr *`.
   - Must have been previously initialized by `edsa_exparr_init()` without having been freed by `edsa_exparr_free()`.
 - Second argument an index which the data will be copied from.
   - Must have been previously written to with `edsa_exparr_ins()`.
 - Third argument an index which the data will be copied to.
   - Array will expand in size if index is outside of array.

Return values:
 - `EDSA_SUCCESS`
   - Returns upon successful run.
 - `EDSA_EXPARR_COPY_INVALID_SRC_INDEX`
   - Returns if the index specified by the second argument is outside bounds allocated by the array.
   - Does not check if index has been previously written to.
 - `EDSA_EXPARR_COPY_INVALID_DEST_INDEX`
   - Returns if the index specified by the third argument would cause the array to be to large to be stored.
 - `EDSA_EXPARR_COPY_REALLOC_FAIL`
   - Returns if `realloc()` fails on the array.
   - Still needs to be freed by `edsa_exparr_free()`.

#### Example
```c
size_t error_val;
edsa_exparr *arr;

...

error_val = edsa_exparr_copy(arr, 0, 1);
```

### `edsa_exparr_read(edsa_exparr *arr, size_t index, void *data)`
Copies data at index `index` from exparr `arr` to `*data`.

Arguments:
 - First argument a pointer of type `edsa_exparr *`.
   - Must have been previously initialized by `edsa_exparr_init()` without having been freed by `edsa_exparr_free()`.
 - Second argument the index from which the data will be read.
   - Does not check if that index has previously been written to.
 - Third arugment a pointer to where the read data will be written.

Return values:
 - `EDSA_SUCCESS`
   - Returns upon successful run.
 - `EDSA_EXPARR_READ_INVALID_INDEX`
   - Returns if a read it attempted at an index that is not allocated for that array.
   - Does not check if data at index has been to written previously.

#### Example
```c
size_t error_val;
edsa_exparr *arr;
char c;

...

error_val = edsa_exparr_read(arr, 1, &c);
```

### Full exparr Example
```c
size_t error_val;
edsa_exparr *arr;
char c = 'c';
char *s = NULL;

error_val = edsa_exparr_init(&arr, 10, sizeof(char));
error_val = edsa_exparr_ins(arr, 1, &c);
error_val = edsa_exparr_read(arr, 1, &c);
error_val = edsa_exparr_copy(arr, 1, 2);
error_val = edsa_exparr_free(arr);
```

## heap
To use a vairable of type `edsa_heap` will need to be created.

### `edsa_heap_init(edsa_heap **heap, size_t heap_size, size_t data_size, int (*cmp_func)(const void *const, const void *const))`
Initalizes heap `heap` with heap size `heap_size` data size `data_size` and compare function `cmp_func`.

Arguments:
 - First argument the address of a pointer of type `edsa_heap *`.
   - Must not have been previously initialized by `edsa_heap_init()` without having been freed by `edsa_heap_free()`.
 - Second argument the amount of elements you would like to be allocated.
   - Must be greater then `0`.
 - Third argument the size of the data type given by `sizeof()`.
 - Fourth argument is a function pointer to a user supplied function that returns type `int`, and takes two arguments of type `const void *const`. Function returns `1` if the element of the heap pointed to by the first argument should be higher up in the heap then the element pointed to by the second element. Returns `0` otherwise.

Return values:
 - `EDSA_SUCCESS`
   - Returns upon successful run.
 - `EDSA_HEAP_INIT_ZERO_ALLOC_SIZE`
   - Returns when `heap_size * data_size` equals 0.
   - Does not need to be freed.
 - `EDSA_HEAP_INIT_MULTIPLICATION_OVERFLOW`
   - Returns when `heap_size * data_size` overflows.
   - Does not need to be freed.
 - `EDSA_HEAP_INIT_MALLOC_FAILED`
   - Returns when `malloc()` fails during call.
   - Does not need to be freed.

#### Example
```c
int cmp_func(const void *const ele_1, const void *const ele_2)
{
  return *((char *) ele_1) > *((char *) ele_2)
}

...

edsa_heap *heap;
size_t ret_val

ret_val = edsa_heap_init(&heap, 10, sizeof(char), cmp_func);
```

### `edsa_heap_change_cmp_func(edsa_heap *heap, int (*cmp_func)(const void *const, const void *const))`
Changes the function used to compare between elements and rebuilds heap `heap`.

Arguments:
 - First argument the a pointer of type `edsa_heap *`.
   - Must not have been previously initialized by `edsa_heap_init()` without having been freed by `edsa_heap_free()`.
 - Second argument is a function pointer to a user supplied function that returns type `int`, and takes two arguments of type `const void *const`. Function returns `1` if the element of the heap pointed to by the first argument should be higher up in the heap then the element pointed to by the second element. Returns `0` otherwise.

Return values:
 - `EDSA_SUCCESS`
   - Returns upon successful run.
 - `EDSA_HEAP_CHANGE_CMP_FUNC_MALLOC_FAIL`
   - Returns when `malloc()` fails during call.
   - Heap should be freed with `edsa_heap_free()`
   - Behaviour of heap when used with any function other than `edsa_heap_free()` is not guaranteed.

#### Example
```c
int new_cmp_func(const void *const ele_1, const void *const ele_2)
{
  return *((char *) ele_1) > *((char *) ele_2)
}

...

edsa_heap *heap;
size_t ret_val

...

ret_val = edsa_heap_change_cmp_func(heap, new_cmp_func);
```

### `edsa_heap_ins(edsa_heap *heap, void *data)`
Inserts data `data` into heap `heap`.

Arguments:
 - First argument the a pointer of type `edsa_heap *`.
   - Must not have been previously initialized by `edsa_heap_init()` without having been freed by `edsa_heap_free()`.
 - Second argument a pointer to data to be inserted.
   - Data must be the same size as supplied to `edsa_heap_init()`.

Return values:
 - `EDSA_SUCCESS`
   - Returns upon successful run.
 - `EDSA_HEAP_INS_HEAP_FULL`
   - Returns if the heap cannot store any more data.
 - `EDSA_HEAP_INS_REALLOC_FAIL`
   - Returns if `realloc()` fails during call.
   - Still needs to be freed by `edsa_heap_free()`.
 - `EDSA_HEAP_INS_MALLOC_FAIL`
   - Returns if `malloc()` fails during call.
   - Still needs to be freed by `edsa_heap_free()`.

#### Example
```c
...

edsa_heap *heap;
int data = 1;
size_t ret_val

...

ret_val = edsa_heap_ins(heap, &data);
```

### `edsa_heap_remove(edsa_heap *heap, void *data)`
Outputs root into `data` and removes the root of the heap `heap` while maintaining the heap condition.

Arguments:
 - First argument the a pointer of type `edsa_heap *`.
   - Must not have been previously initialized by `edsa_heap_init()` without having been freed by `edsa_heap_free()`.
 - Second argument a pointer to where the data will be written.
   - Memory pointed to must be able to hold data of the same size as supplied to `edsa_heap_init()`.

Return values:
 - `EDSA_SUCCESS`
   - Returns upon successful run.
 - `EDSA_HEAP_REMOVE_MALLOC_FAIL`
   - Returns if malloc fails during call.
 - `EDSA_HEAP_REMOVE_HEAP_EMPTY`
   - Returns if the heap is empty.

#### Example
```c
...

edsa_heap *heap;
int data;
size_t ret_val

...

ret_val = edsa_heap_remove(heap, &data);
```

### `edsa_heap_build(edsa_heap *heap, void *arr, size_t amount)`
Builds new heap `heap` from arr `arr` of size `amount`. Previous data stored in heap is inaccessible, but should not be considered erased or overwritten.

Arguments:
 - First argument the a pointer of type `edsa_heap *`.
   - Must not have been previously initialized by `edsa_heap_init()` without having been freed by `edsa_heap_free()`.
 - Second argument is an array with data of the same size as supplied to `edsa_heap_init()`.
 - Third argument is the amount of elements to be added to the heap from the second argument.

Return values:
 - `EDSA_SUCCESS`
   - Returns upon successful run.
 - `EDSA_HEAP_BUILD_REALLOC_FAIL`
   - Returns when `realloc()` fails during call.
   - Heap should be freed with `edsa_heap_free()`
   - Behaviour of heap when used with any function other than `edsa_heap_free()` is not guaranteed.
 - `EDSA_HEAP_BUILD_MALLOC_FAIL`
   - Returns when `malloc()` fails during call.
   - Heap should be freed with `edsa_heap_free()`
   - Behaviour of heap when used with any function other than `edsa_heap_free()` is not guaranteed.
 - `EDSA_HEAP_BUILD_AMOUNT_TO_HIGH`
   - Returns when `amount` would create a heap to large to be stored.
   - Heap should be freed with `edsa_heap_free()`
   - Behaviour of heap when used with any function other than `edsa_heap_free()` is not guaranteed.

#### Example

```c
...

edsa_heap *heap;
int data[100] = ...;
size_t ret_val

...

ret_val = edsa_heap_build(heap, data, 100);
```

### `edsa_heap_free(edsa_heap *heap)`
Frees heap `heap`.

Arguments:
 - First argument the a pointer of type `edsa_heap *`.
   - Must not have been previously initialized by `edsa_heap_init()` without having been freed by `edsa_heap_free()`.

Return values:
 - `EDSA_SUCCESS`
   - Returns upon successful run.

#### Example
```c
...

edsa_heap *heap;
size_t ret_val

...

ret_val = edsa_heap_free(heap);
```

### `edsa_heap_replace(edsa_heap *heap, void *data_in, void *data_out)`
Outputs root into `data_out`, removes the root of the heap `heap` and inserts `data_in` into the heap while maintaining the heap condition. Faster than `edsa_heap_remove()` and `edsa_heap_ins()` on the same data.

Arguments:
 - First argument the a pointer of type `edsa_heap *`.
   - Must not have been previously initialized by `edsa_heap_init()` without having been freed by `edsa_heap_free()`.
 - Second argument a pointer to data to be inserted.
   - Data must be the same size as supplied to `edsa_heap_init()`.
 - Third argument a pointer to where the data will be written.
   - Memory pointed to must be able to hold data of the same size as supplied to `edsa_heap_init()`.

Return values:
 - `EDSA_SUCCESS`
   - Returns upon successful run.
 - `EDSA_HEAP_REPLACE_HEAP_EMPTY`
   - Returns if the heap is empty.
 - `EDSA_HEAP_REPLACE_MALLOC_FAIL`
   - Returns if `malloc()` fails during call.

#### Example
```c
...

edsa_heap *heap;
size_t ret_val
int data = 1;
int buf;

...

ret_val = edsa_heap_replace(heap, &data, &buf);
```

### Full heap Example
```c
int cmp_func(const void *const ele_1, const void *const ele_2)
{
  return *((char *) ele_1) > *((char *) ele_2)
}

int new_cmp_func(const void *const ele_1, const void *const ele_2)
{
  return *((char *) ele_1) > *((char *) ele_2)
}

...

edsa_heap *heap;
size_t ret_val
int data[100] = ...;
int buf;

ret_val = edsa_heap_init(&heap, 1, sizeof(int), cmp_func);
ret_val = edsa_heap_build(heap, data, 20);
ret_val = edsa_heap_ins(heap, &(data[21]));
ret_val = edsa_heap_remove(heap, &buf);
ret_val = edsa_heap_change_cmp_func(heap, new_cmp_func);
ret_val = edsa_heap_replace(heap, &(data[22]), &buf);
ret_val = edsa_heap_free(heap);
```
