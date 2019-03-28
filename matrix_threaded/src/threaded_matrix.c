//
// Created by d on 17/03/19.
//

#include "../include/threaded_matrix.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/matrix.h"

matrix_t* threaded_matrix_sum(matrix_t* matrixA, matrix_t* matrixB, int thread_count) {
    sum_package* sum_content = NULL;
    pthread_t* threads = NULL;

    int total_elements = matrixA->rows * matrixA->cols;
    int elements_per_job = total_elements / thread_count;

    int i;

    if (!(sum_content = (sum_package*) malloc(sizeof(sum_package) * thread_count))) {
        perror("Erro ao alocar memória para o conteúdo!");
        exit(EXIT_FAILURE);
    }

    if (!(threads = (pthread_t*) malloc(sizeof(pthread_t) * thread_count))) {
        perror("Erro ao alocar memória para threads!");
        exit(EXIT_FAILURE);
    }

    matrix_t *resultado = matrix_create(matrixA->rows, matrixA->cols);

    for (i = 0; i < thread_count; i++) {
        sum_content[i].first = matrixA->data;
        sum_content[i].second = matrixB->data;
        sum_content[i].start = i * elements_per_job;
        sum_content[i].end = (i + 1) * elements_per_job;
        sum_content[i].result = resultado->data;

        // Check for final
        if (i == thread_count - 1) {
            sum_content[i].end = total_elements;
        }

        pthread_create(&threads[i], NULL, sum_thread_job, (void *) (sum_content + i));
    }

    for (i = 0; i < thread_count; ++i) {
        pthread_join(threads[i], NULL);
    }

    free(sum_content);
    free(threads);

    return resultado;
}

void* sum_thread_job(void* raw_data) {
    sum_package* data = (sum_package*) raw_data;

    for (int i = data->start; i < data->end; i++) {
        (*data->result)[i] = data->first[0][i] + data->second[0][i];
    }

    return NULL;
}

matrix_t* threaded_matrix_mult(matrix_t* matrixA, matrix_t* matrixB, int thread_count) {
    mult_package* mult_content = NULL;
    pthread_t* threads = NULL;

    int total_elements_mat_b = matrixB->cols;
    int rows_per_job = matrixA->rows / thread_count;

    int i;

    if (!(mult_content = (mult_package*) malloc(sizeof(mult_package) * thread_count))) {
        perror("Erro ao alocar memória para o conteúdo!");
        exit(EXIT_FAILURE);
    }

    if (!(threads = (pthread_t*) malloc(sizeof(pthread_t) * thread_count))) {
        perror("Erro ao alocar memória para threads!");
        exit(EXIT_FAILURE);
    }

    matrix_t *resultado = matrix_create(matrixA->rows, matrixB->cols);

    for (i = 0; i < thread_count; ++i) {
        mult_content[i].first = matrixA->data;
        mult_content[i].second = matrixB->data;
        mult_content[i].first_row = i * rows_per_job;
        mult_content[i].last_row = (i + 1) * rows_per_job;
        mult_content[i].result = resultado->data;
        mult_content[i].total_cols = resultado->cols;

        // Check for final
        if (i == thread_count - 1) {
            mult_content[i].last_row = matrixA->rows;
        }

        pthread_create(&threads[i], NULL, mult_thread_job, (void *) (mult_content + i));
    }

    for (i = 0; i < thread_count; ++i) {
        pthread_join(threads[i], NULL);
    }

    free(mult_content);
    free(threads);

    return resultado;
}

void* mult_thread_job(void* raw_data) {
    mult_package* data = (mult_package*) raw_data;

    for (int i = data->first_row; i < data->last_row; i++) { // Percorre linha da A
        for (int j = 0; j < data->total_cols; j++) {
            data->result[i][j] = 0;
            for (int k = 0; k < data->total_cols; ++k) { // Percorre matrix B
                data->result[i][j] += data->first[i][k] * data->second[k][j];
            }
        }
    }

    return NULL;
}


matrix_t* threaded_matrix_sort(matrix_t* matrix, int thread_count) {
    int rows_final = matrix->rows;
    int cols_final = matrix->cols;

    matrix_t *resultado = matrix_create(rows_final, cols_final);

    memcpy(resultado->data[0], matrix->data[0], cols_final * rows_final * sizeof(double));



    start_bucket_sort(resultado, thread_count);



    return resultado;
}

void start_bucket_sort(matrix_t *matrix,int thread_count) {
    struct bucket buckets[thread_count];

    int rows_final = matrix->rows;
    int cols_final = matrix->cols;
    int total_items = rows_final * cols_final;

    sort_package* sort_content = NULL;
    pthread_t* threads = NULL;

    double* array = matrix->data[0];

    if (!(sort_content = (sort_package*) malloc(sizeof(sort_package) * thread_count))) {
        perror("Erro ao alocar memória para o conteúdo!");
        exit(EXIT_FAILURE);
    }

    if (!(threads = (pthread_t*) malloc(sizeof(pthread_t) * thread_count))) {
        perror("Erro ao alocar memória para threads!");
        exit(EXIT_FAILURE);
    }

    int i, j, k;
    for (i = 0; i < thread_count; i++) {
        buckets[i].count = 0;
        buckets[i].value = (double*)malloc(sizeof(double) * total_items);
    }

    for (i = 0; i < total_items; i++) {
        int index = array[i] * thread_count;
        buckets[index].value[buckets[index].count++] = array[i];
    }

    for (k = 0, i = 0; i < thread_count; i++) {
        // qsort(buckets[i].value, buckets[i].count, sizeof(int), );
        sort_content[i].result = buckets[i].value;
        sort_content[i].end = buckets[i].count;

        pthread_create(&threads[i], NULL, sort_thread_job, (void *) (sort_content + i));
    }

    for (k = 0, i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);

        for (j = 0; j < buckets[i].count; j++) {
            array[k + j] = buckets[i].value[j];
        }

        k += buckets[i].count;
        free(buckets[i].value);
    }
    free(sort_content);
    free(threads);
}


void* sort_thread_job(void* raw_data) {
    sort_package* data = (sort_package*) raw_data;

    quick_sort(data->result, 0, data->end - 1);

    return NULL;
}
