#include <iostream>
#include <vector>
#include <map>
#include <string>

#define _XOPEN_SOURCE 700
#include <signal.h>
#undef _XOPEN_SOURCE

#include <stdlib.h>
#include <unistd.h>

#include <omp.h>
#include <mpi.h>

#include "Master.hpp"
#include "Worker.hpp"

int rank = 0;
int size = 0;

int main(int argc, char **argv)
{
	MPI_Init(nullptr, nullptr);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (Master::IsMaster(rank))
	{
		std::string hashes;
		std::string hash;

		while (std::cin >> hash)
		{
			hashes += hash;
		}
        Master *master = new Master(size, rank, hashes);

		master->Run();
	}
	else
	{
		auto worker = new Worker(size, rank);
		worker->Run();
	}

	MPI_Finalize();
	return 0;
}