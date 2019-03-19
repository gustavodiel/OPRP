//
// Created by d on 17/03/19.
//

#ifndef MATRIX_THREADED_PROJECT_THREADED_MATRIX_H
#define MATRIX_THREADED_PROJECT_THREADED_MATRIX_H

#include "matrix.h"

// Sum

typedef struct {
    double **first;
    double **second;
    double **result;
    int start, end;
} sum_package;

typedef struct {
    double **first;
    double **second;
    double **result;
    int first_row, last_row, total_cols, num_cols_b;
} mult_package;

typedef struct {
    double **result;
    int start, end;
} sort_package;

matrix_t* threaded_matrix_sum(matrix_t*, matrix_t*, int);
void* sum_thread_job(void*);


matrix_t* threaded_matrix_mult(matrix_t*, matrix_t*, int);
void* mult_thread_job(void*);


matrix_t* threaded_matrix_sort(matrix_t*, int);
void* sort_thread_job(void*);
void quick_sort_threaded(double *vector, int low, int high);


#endif //MATRIX_THREADED_PROJECT_THREADED_MATRIX_H
