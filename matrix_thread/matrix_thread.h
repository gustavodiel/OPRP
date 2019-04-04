#ifndef __MATRIX_THREADED_H
#define __MATRIX_THREADED_H

#include <stdlib.h>
#include "matrix.h"


typedef struct {
	double *first;
	double *second;
    double **result;
	int start, end;
} sum_data;

matrix_t *matrix_threaded_sum(matrix_t*, matrix_t*, int);
void* thread_sum_job(void* data);


#endif
