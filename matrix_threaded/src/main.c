#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "matrix.h"
#include "benchmarks.h"

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Uso: %s <rows> <cols>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("\e[1;1H\e[2J");

    int nrows = atoi(argv[1]);
    int ncols = atoi(argv[2]);


    sum_benchmark(nrows, ncols, 100);
    multiply_benchmark(nrows, ncols, 0);
    sort_benchmark(nrows, ncols, 0);

    return EXIT_SUCCESS;
}
