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

matrix_t* threaded_matrix_sum(matrix_t*, matrix_t*, int);
void* sum_thread_job(void*);

#endif //MATRIX_THREADED_PROJECT_THREADED_MATRIX_H
