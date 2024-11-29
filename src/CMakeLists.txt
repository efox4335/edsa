cmake_minimum_required(VERSION 3.29.3)

list(APPEND static_headers ${CMAKE_CURRENT_SOURCE_DIR}/edsa.h)
list(APPEND shared_headers ${CMAKE_CURRENT_SOURCE_DIR}/edsa.h)

set_target_properties(${CMAKE_PROJECT_NAME}_static PROPERTIES PUBLIC_HEADER "${static_headers}")
set_target_properties(${CMAKE_PROJECT_NAME}_shared PROPERTIES PUBLIC_HEADER "${shared_headers}")

add_subdirectory(edsa_stack)
add_subdirectory(edsa_error_codes)
add_subdirectory(edsa_htable)
add_subdirectory(edsa_exparr)
add_subdirectory(edsa_heap)
