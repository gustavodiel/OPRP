#include "Worker.hpp"

#include "Master.hpp"

#include <iostream>

#include <mpi.h>

Worker::Worker(int _size, int _rank) : rank(_rank), size(_size)
{
}

Worker::~Worker()
{
}

void Worker::Run()
{
	std::cout << "Worker with rank " << this->rank << " out of " << this->size << "\n";

	std::string hashes;

	int line_size = hashes.size();
	MPI_Bcast(&line_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

	hashes.resize(line_size);

	MPI_Bcast(const_cast<char *>(hashes.data()), line_size, MPI_CHAR, 0, MPI_COMM_WORLD);

	std::cout << hashes << "\n";

	while (true)
	{
		if (Master::oi != 0)
		{
			std::cout << "Killing worker" << std::endl;
			for (auto i = 0; i < 1000; i++)
			{
				// std::cout << i << ' ';
			}
			break;
		}
	}
}