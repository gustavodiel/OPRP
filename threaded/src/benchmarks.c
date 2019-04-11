//
// Created by d on 16/03/19.
//

#include "../include/benchmarks.h"

#include <math.h>

#include "../include/matrix.h"
#include "../include/threaded_matrix.h"

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + t.tv_usec / 1000000.0;
}

void sum_benchmark(const int rows, const int cols, const int total_executions, int total_threads) {
    double start_time, end_time;
    int repeat = total_executions;

    // Setup benchrmark ###
    matrix_t* matrixA = matrix_create(rows, cols);
    matrix_t* matrixB = matrix_create(rows, cols);
    matrix_t* result;

    matrix_randfill(matrixA);
    matrix_randfill(matrixB);

    double media[total_executions];

    while(repeat --> 0) {
        // Start Benchmark  ###
        start_time = wtime();

        // Process
//        result = matrix_sum(matrixA, matrixB);
        result = threaded_matrix_sum(matrixA, matrixB, total_threads);

        // End Benchmark    ###
        end_time = wtime();

        const double took = end_time - start_time;

        media[repeat] = took;

        // printf("\x1B[34m[\x1B[31mSUM\x1B[34m ] \x1B[37mExecution \x1B[36m%4d \x1B[37mout of \x1B[34m%d \x1B[37mfor \x1B[33m%d x %d \x1B[37mtook \x1B[35m%lf \x1B[37m\n", total_executions - repeat, total_executions, rows, cols, took);

        matrix_destroy(result);
    }

    matrix_destroy(matrixA);
    matrix_destroy(matrixB);

    printf("\x1B[34m[\x1B[31mSUM\x1B[34m ] \x1B[37mTotal: \x1B[35m%lf\x1B[37m, \x1B[37mAverage: \x1B[35m%lf\x1B[37m, deviation: \x1B[35m%lf\x1B[37m for \x1B[34m%d\x1B[37m runs\n\n", total_time(total_executions, media), average(total_executions, media), deviation(total_executions, media), total_executions);
}

void multiply_benchmark(int rows, int cols, int total_executions, int total_threads) {
    double start_time, end_time;
    int repeat = total_executions;

    // Setup benchrmark ###
    matrix_t* matrixA = matrix_create(rows, cols);
    matrix_t* matrixB = matrix_create(rows, cols);
    matrix_t* result;

    matrix_fill(matrixA, 2);
    matrix_fill(matrixB, 4);

    // matrix_randfill(matrixA);
    // matrix_randfill(matrixB);

    double media[total_executions];

    while(repeat --> 0) {
        // Start Benchmark  ###
        start_time = wtime();

        // Process
        // matrix_t* result = matrix_multiply(matrixA, matrixB);
        result = threaded_matrix_mult(matrixA, matrixB, total_threads);

        // End Benchmark    ###
        end_time = wtime();

        const double took = end_time - start_time;

        media[repeat] = took;

        // printf("\x1B[34m[\x1B[33mMULT\x1B[34m] \x1B[37mExecution \x1B[36m%4d \x1B[37mout of \x1B[34m%d \x1B[37mfor \x1B[33m%d x %d \x1B[37mtook \x1B[35m%lf \x1B[37m\n", total_executions - repeat, total_executions, rows, cols, took);

        matrix_destroy(result);
    }

    matrix_destroy(matrixA);
    matrix_destroy(matrixB);

    printf("\x1B[34m[\x1B[33mMULT\x1B[34m] \x1B[37mTotal: \x1B[35m%lf\x1B[37m, \x1B[37mAverage: \x1B[35m%lf\x1B[37m, deviation: \x1B[35m%lf\x1B[37m for \x1B[34m%d\x1B[37m runs\n\n", total_time(total_executions, media), average(total_executions, media), deviation(total_executions, media), total_executions);
}

void sort_benchmark(int rows, int cols, int total_executions, int total_threads) {
    double start_time, end_time;
    int repeat = total_executions;

    // Setup benchrmark ###
    matrix_t* matrixA = matrix_create(rows, cols);
    matrix_t* result;

    matrix_randfill(matrixA);

    double media[total_executions];

    while(repeat --> 0) {
        // Start Benchmark  ###
        start_time = wtime();

        // Process
        // result = matrix_sort(matrixA);
        result = threaded_matrix_sort(matrixA, total_threads);

        // End Benchmark    ###
        end_time = wtime();

        const double took = end_time - start_time;

        media[repeat] = took;

        // printf("\x1B[34m[\x1B[36mSORT\x1B[34m] \x1B[37mExecution \x1B[36m%4d \x1B[37mout of \x1B[34m%d \x1B[37mfor \x1B[33m%d x %d \x1B[37mtook \x1B[35m%lf \x1B[37m\n", total_executions - repeat, total_executions, rows, cols, took);

        int last = 0;
        for (int i = 1; i < result->cols * result->rows; ++i) {
            if (result->data[0][i] < result->data[0][last]) {
                perror("Sort failed");
                exit(EXIT_FAILURE);
            }
            last++;
        }

        matrix_destroy(result);
    }

    matrix_destroy(matrixA);

    printf("\x1B[34m[\x1B[36mSORT\x1B[34m] \x1B[37mTotal: \x1B[35m%lf\x1B[37m, \x1B[37mAverage: \x1B[35m%lf\x1B[37m, deviation: \x1B[35m%lf\x1B[37m for \x1B[34m%d\x1B[37m runs\n\n", total_time(total_executions, media), average(total_executions, media), deviation(total_executions, media), total_executions);
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

double total_time(int num, double* data) {
    double result = 0;
    for (int i = 0; i < num; i++) {
        result += data[i];
    }
    return result;
}
