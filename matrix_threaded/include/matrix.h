#ifndef __MATRIX_H
#define __MATRIX_H

#include <stdlib.h>

#include "benchmarks.h"

#define random() ((rand() ^ rand()) / (RAND_MAX + 1.0))

typedef struct {
      double **data;
      int rows;
      int cols;
} matrix_t;

/*
 * All functions must return a new matriz (when need)
 */


matrix_t *matrix_create(int, int);

void matrix_destroy(matrix_t *);

void matrix_randfill(matrix_t *);

void matrix_fill(matrix_t *, double);

matrix_t *matrix_multiply(matrix_t *, matrix_t *);

matrix_t *matrix_sum(matrix_t *, matrix_t *);

matrix_t *matrix_sort(matrix_t *);

void matrix_print(matrix_t *);

void quicksort(double*, int, int);
void swap(double*, double*);

#endif
