cmake_minimum_required(VERSION 3.29.3)

project(edsa)

add_compile_options(-Wall -Wextra -Wpedantic)

add_link_options(-Wall -Wextra -Wpedantic)

add_library(${CMAKE_PROJECT_NAME}_static STATIC)
add_library(${CMAKE_PROJECT_NAME}_shared SHARED)

target_include_directories(${CMAKE_PROJECT_NAME}_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${CMAKE_PROJECT_NAME}_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src)

enable_testing()

add_subdirectory(tests)

include(CTest)

install(TARGETS
	${CMAKE_PROJECT_NAME}_static
	${CMAKE_PROJECT_NAME}_shared)
