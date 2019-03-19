//
// Created by d on 16/03/19.
//

#ifndef MATRIX_THREADED_PROJECT_BENCHMARKS_H
#define MATRIX_THREADED_PROJECT_BENCHMARKS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

void sum_benchmark(int, int, int);
void multiply_benchmark(int, int , int);
void sort_benchmark(int, int, int);

double deviation(int, double*);
double average(int, double*);
double total_time(int, double*);

#endif //MATRIX_THREADED_PROJECT_BENCHMARKS_H
