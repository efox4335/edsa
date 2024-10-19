cmake_minimum_required(VERSION 3.29.3)

add_library(test_malloc_shared SHARED)
target_sources(test_malloc_shared PRIVATE test_malloc.c)
target_compile_options(test_malloc_shared PRIVATE "-w")#suppresses usless unused parameter warning
