#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include "../include/matrix.h"
#include "../include/benchmarks.h"

int main(int argc, char **argv)
{
    double start_time, end_time;
    int nrows, ncols, exec;

    if ((argc != 4)) {
        printf("Uso: %s <rows> <cols> <num of executions>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    nrows = atoi(argv[1]);
    ncols = atoi(argv[2]);
    exec = atoi(argv[3]);

    sum_benchmark(nrows, ncols, exec);
    multiply_benchmark(nrows, ncols , exec);
    sort_benchmark(nrows, ncols, exec);

    return EXIT_SUCCESS;
}
