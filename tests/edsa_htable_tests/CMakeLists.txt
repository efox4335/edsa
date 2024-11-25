cmake_minimum_required(VERSION 3.29.3)

set(test_sources
	edsa_htable_init_success.c;
	edsa_htable_init_htable_size_zero.c;
	edsa_htable_init_htable_size_too_large.c;
	edsa_htable_free_success.c)

foreach(s_file IN LISTS test_sources)
	string(REPLACE ".c" "" test_names ${s_file})

	add_executable(${test_names}_static ${s_file})
	target_link_libraries(${test_names}_static ${CMAKE_PROJECT_NAME}_static)
	add_test(NAME ${test_names}_static COMMAND ${test_names}_static)

	add_executable(${test_names}_shared ${s_file})
	target_link_libraries(${test_names}_shared ${CMAKE_PROJECT_NAME}_shared)
	add_test(NAME ${test_names}_shared COMMAND ${test_names}_shared)
endforeach()
