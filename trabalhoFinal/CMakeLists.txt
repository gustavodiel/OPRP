### Set the versions
cmake_minimum_required(VERSION 3.0.0)
project(DESCracker VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

### Create project
add_executable(DESCracker Worker.cpp Master.cpp main.cpp)

### Set build flags
set(CMAKE_C_FLAGS "-fopenmp -Ofast")
set(CMAKE_CXX_FLAGS "-fopenmp -Ofast")

target_link_libraries(DESCracker gomp)
target_link_libraries(DESCracker crypt)

## Add MPI
find_package(MPI REQUIRED)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})
target_link_libraries(DESCracker ${MPI_CXX_LIBRARIES})

### CPack stuff
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
