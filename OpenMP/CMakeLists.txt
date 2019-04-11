cmake_minimum_required(VERSION 3.1)

project(open_mp_project)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "")

find_package(OpenMP REQUIRED)

add_executable(open_mp src/matrix.c src/benchmarks.c src/main.c)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

target_link_libraries(open_mp OpenMP::OpenMP_CXX)
target_link_libraries(open_mp Threads::Threads)
target_link_libraries(open_mp m)
