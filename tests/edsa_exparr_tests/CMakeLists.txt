cmake_minimum_required(VERSION 3.29.3)

set(test_sources
	edsa_exparr_basic_func.c;
	edsa_exparr_data_intgr.c;
	edsa_exparr_read_bounds.c;
	edsa_exparr_copy_invalid_src_index.c;
	edsa_exparr_copy_invalid_dest_index.c)

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
	add_executable(edsa_exparr_copy_realloc_fail_static edsa_exparr_copy_realloc_fail.c)
	target_link_libraries(edsa_exparr_copy_realloc_fail_static ${CMAKE_PROJECT_NAME}_static)
	add_test(NAME edsa_exparr_copy_realloc_fail_static COMMAND edsa_exparr_copy_realloc_fail_static)
	set_property(TEST edsa_exparr_copy_realloc_fail_static PROPERTY ENVIRONMENT LD_PRELOAD=../utils/libtest_realloc_shared.so)

	add_executable(edsa_exparr_copy_realloc_fail_shared edsa_exparr_copy_realloc_fail.c)
	target_link_libraries(edsa_exparr_copy_realloc_fail_shared ${CMAKE_PROJECT_NAME}_shared)
	add_test(NAME edsa_exparr_copy_realloc_fail_shared COMMAND edsa_exparr_copy_realloc_fail_shared)
	set_property(TEST edsa_exparr_copy_realloc_fail_shared PROPERTY ENVIRONMENT LD_PRELOAD=../utils/libtest_realloc_shared.so)
endif()
