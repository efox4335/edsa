cmake_minimum_required(VERSION 3.29.3)

get_target_property(static_headers ${CMAKE_PROJECT_NAME}_static PUBLIC_HEADER)
get_target_property(shared_headers ${CMAKE_PROJECT_NAME}_static PUBLIC_HEADER)

list(APPEND static_headers ${CMAKE_CURRENT_SOURCE_DIR}/edsa_error_codes.h)
list(APPEND shared_headers ${CMAKE_CURRENT_SOURCE_DIR}/edsa_error_codes.h)

set_target_properties(${CMAKE_PROJECT_NAME}_static PROPERTIES PUBLIC_HEADER "${static_headers}")
set_target_properties(${CMAKE_PROJECT_NAME}_shared PROPERTIES PUBLIC_HEADER "${shared_headers}")

target_sources(${CMAKE_PROJECT_NAME}_static PUBLIC edsa_error_codes.c)
target_sources(${CMAKE_PROJECT_NAME}_shared PUBLIC edsa_error_codes.c)
