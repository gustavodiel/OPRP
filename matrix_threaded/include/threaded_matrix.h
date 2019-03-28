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
    int first_row, last_row, total_cols;
} mult_package;

typedef struct {
    double *result;
    int end;
} sort_package;

struct bucket
{
    int count;
    double* value;
};

matrix_t* threaded_matrix_sum(matrix_t*, matrix_t*, int);
void* sum_thread_job(void*);


matrix_t* threaded_matrix_mult(matrix_t*, matrix_t*, int);
void* mult_thread_job(void*);


matrix_t* threaded_matrix_sort(matrix_t*, int);
void* sort_thread_job(void*);
void start_bucket_sort(matrix_t *matrix,int thread_count);


#endif //MATRIX_THREADED_PROJECT_THREADED_MATRIX_H
