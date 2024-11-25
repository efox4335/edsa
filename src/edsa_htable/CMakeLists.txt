cmake_minimum_required(VERSION 3.29.3)

target_sources(${CMAKE_PROJECT_NAME}_static PUBLIC edsa_htable.c)
target_sources(${CMAKE_PROJECT_NAME}_shared PUBLIC edsa_htable.c)
