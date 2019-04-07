#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../include/matrix.h"
#include "../include/benchmarks.h"

int main(int argc, char **argv)
{
    // if (argc != 5) {
    //     printf("Uso: %s <rows> <cols> <number of times> <number of threads>\n", argv[0]);
    //     exit(EXIT_FAILURE);
    // }
    //
    // printf("\e[1;1H\e[2J");
    //
    // int nrows = atoi(argv[1]);
    // int ncols = atoi(argv[2]);
    // int nums = atoi(argv[3]);
    // int threads = atoi(argv[4]);

    int sumCols = 10000;
    int multCols = 2000;
    int sortCols = 8000;

    int threads[] = {1, 2, 3, 4, 5 , 6, 7, 8, 16};
    int numTries = 9;

    int tests = 10;

    for (int i = 0; i < numTries; ++i) {
        sum_benchmark(sumCols, sumCols, tests, threads[i]);
    }

    for (int i = 0; i < numTries; ++i) {
        multiply_benchmark(multCols, multCols, tests, threads[i]);
    }

    for (int i = 0; i < numTries; ++i) {
        sort_benchmark(sortCols, sortCols, tests, threads[i]);
    }

    return EXIT_SUCCESS;
}
