cmake_minimum_required(VERSION 3.29.3)

add_executable(edsa_stack_push_pop edsa_stack_push_pop.c)

add_executable(edsa_stack_underflow edsa_stack_underflow.c)

target_link_libraries(edsa_stack_push_pop ${CMAKE_PROJECT_NAME}_static)

target_link_libraries(edsa_stack_underflow ${CMAKE_PROJECT_NAME}_static)

add_test(NAME edsa_stack_push_pop COMMAND edsa_stack_push_pop)

add_test(NAME edsa_stack_underflow COMMAND edsa_stack_underflow)
