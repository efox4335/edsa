cmake_minimum_required(VERSION 3.29.3)

project(edsa)

add_compile_options(-Wall -Wextra -Wpedantic)

add_link_options(-Wall -Wextra -Wpedantic)

add_library(${CMAKE_PROJECT_NAME}_static STATIC)
add_library(${CMAKE_PROJECT_NAME}_shared SHARED)

add_subdirectory(src)

enable_testing()

add_subdirectory(tests)



include(CTest)
