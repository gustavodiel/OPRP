#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/matrix.h"

matrix_t *matrix_create(int rows, int cols)
{
    matrix_t *matrix;
    if (!(matrix = (matrix_t*) malloc(sizeof(matrix_t)))) {
        perror("Failed to allocate memory!\n");
        exit(EXIT_FAILURE);
    }

    matrix->rows = rows;
    matrix->cols = cols;

    matrix->data = (double**)malloc(sizeof(double*) * rows);

    double *temp = (double*)malloc(sizeof(double) * rows * cols);

    int i;

    for (i = 0; i < rows; i++) {
      matrix->data[i] = (temp + (i * rows));
    }

    return matrix;
}

void matrix_destroy(matrix_t *matrix)
{
    free(*matrix->data);

    int i;
    for (i = 0; i < matrix->rows; i++) {
      matrix->data[i] = NULL;
    }

    matrix->data = NULL;

    free(matrix);
}

void matrix_randfill(matrix_t *matrix)
{
   int i, j;
   for (i = 0; i < matrix->rows; i++) {
      for (j = 0; j < matrix->cols; j++) {
          matrix->data[i][j] = random();
      }
   }
}

void matrix_fill(matrix_t *matrix, double val)
{
   int i, j;
   for (i = 0; i < matrix->rows; i++) {
      for (j = 0; j < matrix->cols; j++) {
          matrix->data[i][j] = val;
      }
   }
}

matrix_t *matrix_multiply(matrix_t *matrixA, matrix_t *matrixB)
{
    int rows_final = matrixA->rows;
    int cols_final = matrixB->cols;

    matrix_t *resultado = matrix_create(rows_final, cols_final);
    matrix_fill(resultado, 0);

    int i, j, k;

    for (i = 0; i < rows_final; i++) {
        for (j = 0; j < cols_final; j++) {
            for (k = 0; k < matrixB->rows; k++) {
                resultado->data[i][j] += matrixA->data[i][k] * matrixB->data[j][k];
            }
        }
    }

    return resultado;
}

void matrix_print(matrix_t *matrix)
{

   int i, j;
   for (i = 0; i < matrix->rows; i++) {
      for (j = 0; j < matrix->cols; j++) {
         printf("%.17f ", matrix->data[i][j]);
      }
      printf("\n");
   }
   fflush(stdout);
}

matrix_t *matrix_sum(matrix_t *matrixA, matrix_t *matrixB)
{
    int rows_final = max(matrixA->rows, matrixB->rows);
    int cols_final = max(matrixA->cols, matrixB->cols);

    matrix_t *resultado = matrix_create(rows_final, cols_final);
    matrix_fill(resultado, 0);

    int i, j;

    for (i = 0; i < rows_final; i++) {
        for (j = 0; j < cols_final; j++) {
            resultado->data[i][j] += matrixA->data[i][j] + matrixB->data[i][j];
        }
    }

    return resultado;
}

matrix_t *matrix_sort(matrix_t *matrixA) {
    int rows = matrixA->rows;
    int cols = matrixA->cols;

    matrix_t *resultado = matrix_create(rows, cols);

    memcpy(resultado->data[0], matrixA->data[0], sizeof(double) * rows * cols);

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
