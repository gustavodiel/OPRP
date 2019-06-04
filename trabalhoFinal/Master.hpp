#pragma once

#include <vector>
#include <string>

#include "Worker.hpp"

class Master : public Worker
{
private:
	/* Data */
	std::string hashes;

public:
	Master(int, int, std::string);
	~Master();

	void Run();

	void SigHandler(int);

	static int oi;

	static int IsMaster(int rank) { return rank == 0; }
};
