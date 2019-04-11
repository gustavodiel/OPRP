#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../include/matrix.h"
#include "../include/benchmarks.h"

int main(int argc, char **argv)
{
    int sumCols = 10000;
    int multCols = 2000;
    int sortCols = 8000;

    int threads[] = {1, 2, 3, 4, 5 , 6, 7, 8, 16};
    int numTries = sizeof(threads) / sizeof(threads[0]);

    int tests = 10;

    for (int i = 0; i < numTries; ++i) {
        sum_benchmark(sumCols, sumCols, tests, threads[i]);
    }

    for (int i = 0; i < numTries; ++i) {
        sort_benchmark(sortCols, sortCols, tests, threads[i]);
    }

    for (int i = 0; i < numTries; ++i) {
        multiply_benchmark(multCols, multCols, tests, threads[i]);
    }


    return EXIT_SUCCESS;
}
