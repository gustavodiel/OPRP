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

    int total_rows = matrixA->rows;
    int total_elements_mat_b = matrixB->cols;
    int rows_per_job = total_rows / thread_count;

    int i;

    if (!(mult_content = (mult_package*) malloc(sizeof(mult_package) * thread_count))) {
        perror("Erro ao alocar memória para o conteúdo!");
        exit(EXIT_FAILURE);
    }

    if (!(threads = (pthread_t*) malloc(sizeof(pthread_t) * thread_count))) {
        perror("Erro ao alocar memória para threads!");
        exit(EXIT_FAILURE);
    }

    matrix_t *resultado = matrix_create(matrixA->rows, matrixA->cols);

    for (i = 0; i < thread_count; ++i) {
        mult_content[i].first = matrixA->data;
        mult_content[i].second = matrixB->data;
        mult_content[i].first_row = i * rows_per_job;
        mult_content[i].last_row = (i + 1) * rows_per_job;
        mult_content[i].result = resultado->data;
        mult_content[i].total_cols = resultado->cols;
        mult_content[i].num_cols_b = matrixB->cols;

        // Check for final
        if (i == thread_count - 1) {
            mult_content[i].last_row = total_rows;
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
        for (int j = 0; j < data->total_cols; ++j) { // Percorre matrix B
            for (int k = 0; k < data->num_cols_b; k++) {
                data->result[i][j] += data->first[i][j] * data->second[j][k];
            }
        }
    }

    return NULL;
}


matrix_t* threaded_matrix_sort(matrix_t* matrix, int thread_count) {
    int rows_final = matrix->rows;
    int cols_final = matrix->cols;
    int total_items = rows_final * cols_final - 1;
    int elements_per_thread = total_items / thread_count;

    sort_package* sort_content = NULL;
    pthread_t* threads = NULL;

    matrix_t *resultado = matrix_create(rows_final, cols_final);

    memcpy(resultado->data[0], matrix->data[0], cols_final * rows_final * sizeof(double));

    if (!(sort_content = (sort_package*) malloc(sizeof(sort_package) * thread_count))) {
        perror("Erro ao alocar memória para o conteúdo!");
        exit(EXIT_FAILURE);
    }

    if (!(threads = (pthread_t*) malloc(sizeof(pthread_t) * thread_count))) {
        perror("Erro ao alocar memória para threads!");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < thread_count; ++i) {
        sort_content[i].start = i * elements_per_thread;
        sort_content[i].end = (i + 1) * elements_per_thread;
        sort_content[i].result = resultado->data;

        // Check for final
        if (i == thread_count - 1) {
            sort_content[i].end = total_items;
        }
        
        pthread_create(&threads[i], NULL, sort_thread_job, (void *) (sort_content + i));
    }

    for (int i = 0; i < thread_count; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Ainda não funciona :nervoso:
    // Falta executar o último loop. pois cada parte está sortada, porém nao como um todo
    // Descomentar essa linha iria arrumar, porém fica lento :eyes:
    // quick_sort(resultado->data[0], 0, total_items);

    // Ideia: fazer bucket sort, dai funciona com n threads

    free(sort_content);
    free(threads);

    return resultado;
}


void* sort_thread_job(void* raw_data) {
    sort_package* data = (sort_package*) raw_data;

    quick_sort(data->result[0], data->start, data->end);

    return NULL;
}

