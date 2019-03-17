#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/matrix.h"

matrix_t *matrix_create(int rows, int cols)
{
    matrix_t *matrix = (matrix_t*)malloc(sizeof(matrix_t));
    matrix->rows = rows;
    matrix->cols = cols;

    matrix->data = (double**)malloc(sizeof(double*) * rows);

    double *temp = (double*)malloc(sizeof(double) * rows * cols);

    int i;

    for (i = 0; i < rows; i++) {
      matrix->data[i] = (i*rows + temp);
    }

    return matrix;
}

void matrix_destroy(matrix_t *matrix)
{
    free(matrix->data[0]);

    int i;
    for (i = 0; i < matrix->rows; i++) {
      matrix->data[i] = NULL;
    }

    free(matrix->data);
    matrix->data = NULL;

    free(matrix);
    matrix = NULL;
}

void matrix_randfill(matrix_t *m)
{
   int i, j;
   for (i = 0; i < m->rows; i++) {
      for (j = 0; j < m->cols; j++) {
         m->data[i][j] = random();
      }
   }
}

void matrix_fill(matrix_t *m, double val)
{
   int i, j;
   for (i = 0; i < m->rows; i++) {
      for (j = 0; j < m->cols; j++) {
         m->data[i][j] = val;
      }
   }
}

matrix_t *matrix_multiply(matrix_t *A, matrix_t *B)
{
    int rows_final = A->rows;
    int cols_final = B->cols;

    matrix_t *resultado = matrix_create(rows_final, cols_final);
    matrix_fill(resultado, 0);

    int i, j, k;

    for (i = 0; i < rows_final; i++) {
        for (j = 0; j < cols_final; j++) {
            for (k = 0; k < B->rows; k++) {
                resultado->data[i][j] += A->data[i][k] * B->data[j][k];
            }
        }
    }

    return resultado;
}

void matrix_print(matrix_t *m)
{

   int i, j;
   for (i = 0; i < m->rows; i++) {
      for (j = 0; j < m->cols; j++) {
         printf("%.17f ", m->data[i][j]);
      }
      printf("\n");
   }
   fflush(stdout);
}

matrix_t *matrix_sum(matrix_t *A, matrix_t *B)
{
    int rows_final = A->rows;
    int cols_final = A->cols;

    matrix_t *resultado = matrix_create(rows_final, cols_final);
    matrix_fill(resultado, 0);

    int i, j;

    for (i = 0; i < rows_final; i++) {
        for (j = 0; j < cols_final; j++) {
            resultado->data[i][j] += A->data[i][j] + B->data[i][j];
        }
    }

    return resultado;
}

matrix_t *matrix_sort(matrix_t *A) {
    int rows = A->rows;
    int cols = A->cols;

    matrix_t *resultado = matrix_create(rows, cols);

    memcpy(resultado->data[0], A->data[0], sizeof(double) * rows * cols);

    quicksort(resultado->data[0], 0, rows * cols - 1);

    return resultado;
}

int partition(double *data, int low, int high) {
    double pivot = data[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++) {
        if (data[j] <= pivot) {
            i++;
            swap(&data[i], &data[j]);
        }
    }
    swap(&data[i + 1], &data[high]);
    return (i + 1);
}

void quicksort(double *data, int low, int high) {
    if (low < high) {
        int pi = partition(data, low, high);

        quicksort(data, low, pi - 1);
        quicksort(data, pi + 1, high);
    }
}
void swap(double *a, double *b) {
    double aux = *a;
    *a = *b;
    *b = aux;
}
