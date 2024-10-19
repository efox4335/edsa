# Edsa Readme
A data structures and algorithms library written in c.
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
Must include `edsa.h` in `src/` directory. Must link aginst either `libedsa_shared.so` or `libedsa_static.a` from `builds/` directory.

## exparr
To use exparr a vairable of type `edsa_exparr *` will need to be created.

### `edsa_exparr_init()`
Initalizes an exparr data structure.

Arguments:
 - First argument the address of the `edsa_exparr *` vairable.
   - Must not have been previously initialized by `edsa_exparr_init()` without having been freed by `edsa_exparr_free()`.
 - Second argument the amount of elements you would like to be allocated.
   - Must be greater then 0.
 - Third argument the size of the data type given by `sizeof()`.

Return values:
 - `EDSA_SUCCESS`
   - Returns upon successful run.
 - `EDSA_EXPARR_INTI_ZERO_ALLOC_SIZE`
   - Returns when `arr_size * data_size` equals 0.
 - `EDSA_EXPARR_INIT_MULTIPLICATION_OVERFLOW`
   - Returns when `arr_size * data_size` overflows.
 - `EDSA_EXPARR_INIT_MALLOC_FAILED`
   - Returns when `malloc()` fails does not need to be freed.

#### Example
```c
size_t error_val;
edsa_exparr *arr;

error_val = edsa_exparr_init(&arr, 10, sizeof(char));
```

### `edsa_exparr_free()`
Frees an exparr data structure.

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

### `edsa_exparr_ins()`
Inserts data into exparr at specified index.

Arguments:
 - First argument a pointer of type `edsa_exparr *`.
   - Must have been previously initialized by `edsa_exparr_init()` without having been freed by `edsa_exparr_free()`.
 - Second argument an index at which the data will be put.
   - Array will expand in size if index is outside of array.
 - Third argument a pointer to the data to be inserted.

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

### `edsa_exparr_read()`
Reads data from exparr and stores at location pointed to by third argument.

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

error_val = edsa_exparr_init(&arr, 10, sizeof(char));
error_val = edsa_exparr_ins(arr, 1, &c);
error_val = edsa_exparr_read(arr, 1, &c);
error_val = edsa_exparr_free(arr);
```

## heap
To use a vairable of type `edsa_heap` will need to be created.

### `edsa_heap_init()`
Initalizes a heap data structure.

Arguments:
 - First argument the address of a pointer of type `edsa_heap`.
   - Must not have been previously initialized by `edsa_heap_init()` without having been freed by `edsa_heap_free()`.
 - Second argument the amount of elements you would like to be allocated.
   - Must be greater then `0`.
 - Third argument the size of the data type given by `sizeof()`.
 - Fourth argument is a function pointer to a user supplied function that returns type `int`, and takes two arguments of type `const void *const`. Function returns `1` if the element of the heap pointed to by the first argument should be higher up in the heap then the element pointed to by the second element. Returns `0` otherwise.

Return values:
 - `EDSA_SUCCESS`
   - Returns upon successful run.
 - `EDSA_HEAP_INTI_ZERO_ALLOC_SIZE`
   - Returns when `heap_size * data_size` equals 0.
 - `EDSA_HEAP_INIT_MULTIPLICATION_OVERFLOW`
   - Returns when `heap_size * data_size` overflows.
 - `EDSA_HEAP_INIT_MALLOC_FAILED`
   - Returns when `malloc()` fails does not need to be freed.

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
