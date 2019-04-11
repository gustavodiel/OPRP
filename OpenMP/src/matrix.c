#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <omp.h>

#include "../include/matrix.h"

matrix_t *matrix_create(int rows, int cols) {
    matrix_t *matrix = (matrix_t*)malloc(sizeof(matrix_t));
    matrix->rows = rows;
    matrix->cols = cols;

    matrix->data = (double**)malloc(sizeof(double*) * rows);

    double *temp = (double*)malloc(sizeof(double) * rows * cols);

    for (int i = 0; i < rows; i++) {
      matrix->data[i] = (i*rows + temp);
    }

    return matrix;
}

void matrix_destroy(matrix_t *matrix) {
    free(matrix->data[0]);

    for (int i = 0; i < matrix->rows; i++) {
      matrix->data[i] = NULL;
    }

    free(matrix->data);
    matrix->data = NULL;

    free(matrix);
    matrix = NULL;

    return;
}

void matrix_randfill(matrix_t *m) {
   for (int i = 0; i < m->rows; i++) {
      for (int j = 0; j < m->cols; j++) {
         m->data[i][j] = random();
      }
   }
}

void matrix_fill(matrix_t *m, double val) {
   for (int i = 0; i < m->rows; i++) {
      for (int j = 0; j < m->cols; j++) {
         m->data[i][j] = val;
      }
   }
}

matrix_t *matrix_multiply(matrix_t *A, matrix_t *B) {
    int rows_final = A->rows;
    int cols_final = B->cols;

    matrix_t *resultado = matrix_create(rows_final, cols_final);
    matrix_fill(resultado, 0);

    int i, j, k;

#pragma omp parallel for private(i, j, k) default(shared)
    for (i = 0; i < rows_final; i++) {
        for (j = 0; j < cols_final; j++) {
            for (k = 0; k < B->rows; k++) {
                resultado->data[i][j] += A->data[i][k] * B->data[k][j];
            }
        }
    }

    return resultado;
}

void matrix_print(matrix_t *m) {

   int i, j;
   for (i = 0; i < m->rows; i++) {
      for (j = 0; j < m->cols; j++) {
         printf("%.17f ", m->data[i][j]);
      }
      printf("\n");
   }
   fflush(stdout);
}

matrix_t *matrix_sum(matrix_t *A, matrix_t *B) {
    int rows_final = max(A->rows, B->rows);
    int cols_final = max(A->cols, B->cols);

    int i, j;

    matrix_t *resultado = matrix_create(rows_final, cols_final);

#pragma omp parallel for private(i, j) shared(resultado, A, B)
    for (i = 0; i < rows_final; i++) {
        for (j = 0; j < cols_final; j++) {
            resultado->data[i][j] = A->data[i][j] + B->data[i][j];
        }
    }

    return resultado;
}

matrix_t *matrix_sort(matrix_t *A) {
    int rows_final = A->rows;
    int cols_final = A->cols;

    matrix_t *resultado = matrix_create(rows_final, cols_final);

    memcpy(resultado->data[0], A->data[0], cols_final * rows_final * sizeof(double));

    quick_sort(resultado->data[0], 0, rows_final * cols_final - 1, 0);

    return resultado;
}

int partition(double *vector, int low, int high) {
    double pivot = vector[high];
    int i = (low - 1);
    int j;

    for (j = low; j <= high - 1; j++)
    {
        if (vector[j] <= pivot)
        {
            i++;

            swap(&vector[i], &vector[j]);
        }
    }
    swap(&vector[i + 1], &vector[high]);
    return (i + 1);
}

void quick_sort(double *vector, int low, int high, int deep) {
    if (low < high) {
        int part = partition(vector, low, high);

        if (deep * 2 > omp_get_num_threads()) {
            quick_sort(vector, low, part - 1, deep + 1);
            quick_sort(vector, part + 1, high, deep + 1);
            return;
        }

        #pragma omp parallel
        {
            #pragma omp sections
            {
                #pragma omp section
                {
                    quick_sort(vector, low, part - 1, deep + 1);
                }

                #pragma omp section
                {
                    quick_sort(vector, part + 1, high, deep + 1);
                }
            }
        }
    }
}

void swap(double *a, double *b) {
    double aux = *a;
    *a = *b;
    *b = aux;
}
