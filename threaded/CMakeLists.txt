cmake_minimum_required(VERSION 3.1)

project(matrix_threaded_project)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#Bring the headers, such as Student.h into the project
#include_directories(include)

add_executable(matrix_threaded src/matrix.c src/benchmarks.c src/main.c src/threaded_matrix.c)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

target_link_libraries(matrix_threaded Threads::Threads)
target_link_libraries(matrix_threaded m)
