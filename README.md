# Edsa Readme
A data structures and algorithms library written in c.
## Supported data structures/algorithms
| Data structure/Algorithm | Description |
| --- | --- |
| exparr | An array that expands to fit data new elements added. Supports arbitrary typed and sized data. |
## Build and Installation Instructions
### Linux
From the root of the project directory run this command.

```cmake -S . --preset=release && cmake --build --preset=release```
### Windows 
Untested.
### Macos
Untested.

## exparr
To use exparr a vairable of type `edsa_exparr *` will need to be created.

###  `edsa_exparr_init()`
Initalizes an exparr data structure.

Arguments:
 - First argument the address of the `edsa_exparr *` vairable.
 - Second argument the amount of elements you would like to be allocated cannot be 0.
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
error_val = edsa_exparr_init(&arr, 10, sizeof(char));
```
