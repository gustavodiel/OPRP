#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "matrix_thread.h"


matrix_t *matrix_threaded_sum(matrix_t *A, matrix_t *B, int num_threads)
{
	sum_data *all_data = NULL;
	pthread_t *threads = NULL;

	int total_nums = A->rows * A->cols;

	int i;

	if (!(all_data = (sum_data *) malloc(sizeof(sum_data) * num_threads))) {
		printf("Erro ao alocar memória\n");
		exit(EXIT_FAILURE);
	}

	if (!(threads = (pthread_t *) malloc(sizeof(pthread_t) * num_threads))) {
		printf("Erro ao alocar memória\n");
		exit(EXIT_FAILURE);
	}

	int num_per_thread = total_nums / num_threads;

	double** result_data = (double**)malloc(sizeof(double) * total_nums);

	for (i = 0; i < num_threads; i++) {
		all_data[i].first = A->data;
		all_data[i].second = B->data;
		all_data[i].start = i * num_per_thread;
		all_data[i].end = (i + 1) * num_per_thread - 1;
		pthread_create(&threads[i], NULL, thread_sum_job, (void *) (all_data + i));
	}

	for (i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	matrix_t *resultado = matrix_create(A->rows, A->cols);
	// resultado->data = result_data;

	return resultado;
}

void* thread_sum_job(void* raw_data) {
	sum_data* data = (sum_data*)raw_data;

	int start = data->start;
    int end = data->end;

	double** firstData = data->first;
	double** secondData = data->second;
	double** result = data->result;

    int i;

	printf("Reading at: %d\n", start);
	printf("Reading: %lf\n", *firstData[start]);

    // for (i = start; i < end; i++) {
    // 	*result[i] = *firstData[i] + *secondData[i];
    // }

    return NULL;
}
