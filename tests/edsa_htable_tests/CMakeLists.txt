cmake_minimum_required(VERSION 3.29.3)

set(test_sources
	edsa_htable_init_success.c;
	edsa_htable_init_htable_size_zero.c;
	edsa_htable_init_htable_size_too_large.c;
	edsa_htable_free_success.c;
	edsa_htable_ins_success.c;
	edsa_htable_read_success.c;
	edsa_htable_read_no_entry.c;
	edsa_htable_read_output.c;
	edsa_htable_remove_success.c;
	edsa_htable_remove_no_entry.c;
	edsa_htable_remove_output.c)

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
	add_executable(edsa_htable_init_malloc_fail_static edsa_htable_init_malloc_fail.c)
	target_link_libraries(edsa_htable_init_malloc_fail_static ${CMAKE_PROJECT_NAME}_static)
	add_test(NAME edsa_htable_init_malloc_fail_static COMMAND edsa_htable_init_malloc_fail_static)
	set_property(TEST edsa_htable_init_malloc_fail_static PROPERTY ENVIRONMENT LD_PRELOAD=../utils/libtest_malloc_shared.so)

	add_executable(edsa_htable_init_malloc_fail_shared edsa_htable_init_malloc_fail.c)
	target_link_libraries(edsa_htable_init_malloc_fail_shared ${CMAKE_PROJECT_NAME}_shared)
	add_test(NAME edsa_htable_init_malloc_fail_shared COMMAND edsa_htable_init_malloc_fail_shared)
	set_property(TEST edsa_htable_init_malloc_fail_shared PROPERTY ENVIRONMENT LD_PRELOAD=../utils/libtest_malloc_shared.so)
endif()
