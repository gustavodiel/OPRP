#ifndef __MATRIX_H
#define __MATRIX_H

#include <stdlib.h>

#define random() ((rand() ^ rand()) / (RAND_MAX + 1.0))

typedef struct {
      double **data;
      int rows;
      int cols;
} matrix_t;

/*
 * All functions must return a new matriz (when need)
 */


matrix_t *matrix_create(int rows, int cols);

void matrix_destroy(matrix_t *m);

void matrix_randfill(matrix_t *m);

void matrix_fill(matrix_t *m, double val);

matrix_t *matrix_multiply(matrix_t *A, matrix_t *B);

matrix_t *matrix_sum(matrix_t *A, matrix_t *B);

matrix_t *matrix_sort(matrix_t *A);

void matrix_print(matrix_t *m);

int partition (double vector[], int low, int high);
void quick_sort(double vector[], int low, int high);
void swap(double *a, double *b);

#endif
