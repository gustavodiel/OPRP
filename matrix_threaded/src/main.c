#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../include/matrix.h"
#include "../include/benchmarks.h"

int main(int argc, char **argv)
{
    if (argc != 4) {
        printf("Uso: %s <rows> <cols> <number of times>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("\e[1;1H\e[2J");

    int nrows = atoi(argv[1]);
    int ncols = atoi(argv[2]);
    int nums = atoi(argv[3]);


    sum_benchmark(nrows, ncols, nums);
    multiply_benchmark(nrows, ncols, nums);
    sort_benchmark(nrows, ncols, nums);

    return EXIT_SUCCESS;
}
