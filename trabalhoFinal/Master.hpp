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

	static int IsMaster(int rank) { return rank == 0; }

	static inline void GetWordSalt(std::string&, char*);

protected:
    std::string GetNextWord(int hashesIndex) override;
};
