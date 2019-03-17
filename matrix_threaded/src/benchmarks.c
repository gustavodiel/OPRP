//
// Created by d on 16/03/19.
//

#include "benchmarks.h"

#include <math.h>

#include "matrix.h"

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + t.tv_usec / 1000000.0;
}

void sum_benchmark(const int rows, const int cols, const int total_executions) {
    double start_time, end_time;
    int repeat = total_executions;

    // Setup benchrmark ###
    matrix_t* matrixA = matrix_create(rows, cols);
    matrix_t* matrixB = matrix_create(rows, cols);

    matrix_randfill(matrixA);
    matrix_randfill(matrixB);

    double media[total_executions];

    while(repeat --> 0) {
        // Start Benchmark  ###
        start_time = wtime();

        // Process
        matrix_sum(matrixA, matrixB);

        // End Benchmark    ###
        end_time = wtime();

        const double took = end_time - start_time;

        media[repeat] = took;

        printf("\x1B[34m[\x1B[31mSUM\x1B[34m] \x1B[37mExecution \x1B[36m%4d \x1B[37mout of \x1B[34m%d \x1B[37mfor \x1B[33m%d x %d \x1B[37mtook \x1B[35m%lf \x1B[37m\n", total_executions - repeat, total_executions, rows, cols, took);
    }



    printf("\x1B[34m[\x1B[31mSUM\x1B[34m] \x1B[37mAverage: \x1B[35m%lf\x1B[37m, deviation: \x1B[35m%lf\x1B[37m for \x1B[34m%d\x1B[37m runs\n", average(total_executions, media), deviation(total_executions, media), total_executions);
}

void multiply_benchmark(int rows, int cols, int repeat) {

}

void sort_benchmark(int rows, int cols, int repeat) {

}

double deviation(int num, double* data) {
    double sum = 0.0, mean, standardDeviation = 0.0;

    int i;

    for(i=0; i<num; ++i)
    {
        sum += data[i];
    }

    mean = sum/num;

    for(i=0; i<num; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation/num);
}

double average(int num, double* data) {
    double result = 0;
    for (int i = 0; i < num; i++) {
        result += data[i];
    }
    return result / num;
}