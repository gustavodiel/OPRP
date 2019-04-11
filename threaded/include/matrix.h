#ifndef __MATRIX_H
#define __MATRIX_H

#include <stdlib.h>

#define random() ((rand() ^ rand()) / (RAND_MAX + 1.0))
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


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

void quick_sort(double*, int, int);
void swap(double*, double*);

#endif
