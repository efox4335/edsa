cmake_minimum_required(VERSION 3.29.3)

set(test_sources
	edsa_heap_free_leak.c;
	edsa_heap_init_mul_overflow.c;
	edsa_heap_init_zero_alloc_size.c;
	edsa_heap_init_success.c;
	edsa_heap_change_cmp_func_success.c;
	edsa_heap_change_cmp_func_output.c;
	edsa_heap_ins_success.c;
	edsa_heap_ins_heap_full.c;
	edsa_heap_remove_success.c;
	edsa_heap_remove_heap_empty.c;
	edsa_heap_remove_output.c;
	edsa_heap_replace_success.c;
	edsa_heap_replace_heap_empty.c;
	edsa_heap_replace_output.c;
	edsa_heap_build_success.c;
	edsa_heap_build_output.c)

foreach(s_file IN LISTS test_sources)
	string(REPLACE ".c" "" test_names ${s_file})

	add_executable(${test_names}_static ${s_file})
	target_link_libraries(${test_names}_static ${CMAKE_PROJECT_NAME}_static)
	add_test(NAME ${test_names}_static COMMAND ${test_names}_static)

	add_executable(${test_names}_shared ${s_file})
	target_link_libraries(${test_names}_shared ${CMAKE_PROJECT_NAME}_shared)
	add_test(NAME ${test_names}_shared COMMAND ${test_names}_shared)
endforeach()

if(${LINUX} AND NOT ${ADRSAN})
	add_executable(edsa_heap_init_malloc_fail_static edsa_heap_init_malloc_fail.c)
	target_link_libraries(edsa_heap_init_malloc_fail_static ${CMAKE_PROJECT_NAME}_static)
	add_test(NAME edsa_heap_init_malloc_fail_static COMMAND edsa_heap_init_malloc_fail_static)
	set_property(TEST edsa_heap_init_malloc_fail_static PROPERTY ENVIRONMENT LD_PRELOAD=../utils/libtest_malloc_shared.so)

	add_executable(edsa_heap_init_malloc_fail_shared edsa_heap_init_malloc_fail.c)
	target_link_libraries(edsa_heap_init_malloc_fail_shared ${CMAKE_PROJECT_NAME}_shared)
	add_test(NAME edsa_heap_init_malloc_fail_shared COMMAND edsa_heap_init_malloc_fail_shared)
	set_property(TEST edsa_heap_init_malloc_fail_shared PROPERTY ENVIRONMENT LD_PRELOAD=../utils/libtest_malloc_shared.so)
endif()
