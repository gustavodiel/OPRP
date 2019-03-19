//
// Created by d on 17/03/19.
//

#include "../include/threaded_matrix.h"

#include <pthread.h>
#include <stdio.h>

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
