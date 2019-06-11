#pragma once

#include <string>
#include <sstream>

class Worker
{
protected:
	int size, rank;
	int hashesIndex;

	unsigned long long int passwordsIndex;

	std::string hashes;

public:
	Worker(int, int);
	~Worker();

	void Run();
	std::string GetNextWord();
	std::string GetWordSalt(std::string);
	std::string GenerateNextPassword(int);

private:
	void ConvertBase(unsigned long long int, int, std::stringstream *);
	unsigned long long int InitializeIndex(int);
};
