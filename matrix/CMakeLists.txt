cmake_minimum_required(VERSION 3.1)

project(matrix_project)

#Bring the headers, such as Student.h into the project
#include_directories(include)

add_executable(matrix src/matrix.c src/benchmarks.c src/main.c)

target_link_libraries(matrix m)
