# [ORPR] - Programação Paralela UDESC - Trabalho Final

## Requirements
- C++ compiler :eyes:
- OpenMP
- OpenMPI

## Building
### CMake
```sh
cd diel_gabriela
mkdir build
cd build
cmake ../
make
```

And you are done!

## Running
```sh
mpirun -machinefile ../machines.txt ./DESCracker < ../inputTrabalho
```