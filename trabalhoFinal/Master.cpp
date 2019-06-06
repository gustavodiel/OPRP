#include "Master.hpp"

#include <iostream>
#include <chrono>
#include <thread>

#include <mpi.h>

int Master::oi = 0;

Master::Master(int size, int rank, std::string hashes) : Worker(size, rank), hashes(hashes)
{
}

Master::~Master()
{
}

void Master::SigHandler(int s)
{
	std::cout << "Got " << s << std::endl;
}

void Master::Run()
{
	std::cout << "Master with rank " << this->rank << " out of " << this->size << "\n";

	int line_size = hashes.size();
	MPI_Bcast(&line_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(const_cast<char *>(hashes.data()), line_size, MPI_CHAR, 0, MPI_COMM_WORLD);

	// while (true)
	// {

	// 	if (Master::oi != 0)
	// 	{
	// 		std::cout << "Saving..." << std::endl;
	// 		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	// 		std::cout << "Saved!" << std::endl;
	// 		break;
	// 	}
	// }
}