# [ORPR] - Programação Paralela UDESC

This repository is where I'll be updating my parallel computing class code.

## Requirements
- C compiler :eyes:
- We will be using CMake in most of the projects

## Building
### CMake
This will apply for those projects with a `CMakeLists.txt` file:
```sh
cd project_folder
mkdir build
cd build
cmake ../
make
```

And you are done!

## Sub-Projects
- [<strong>Matrix</strong>](/matrix/): In this base code, we will, eventually, use multiple techniques to parallelize and gain performance.
- [<strong>Multithreaded Matrix</strong>](/matrix_threaded): This will be where we will implement mult-thread functionality, based on the Matrix project.

