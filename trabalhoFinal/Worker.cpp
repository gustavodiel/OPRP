#include "Worker.hpp"

#include "Master.hpp"

#include <iostream>
#include <map>
#include <cmath>

#include <mpi.h>
#include <crypt.h>

Worker::Worker(int _size, int _rank) : rank(_rank), size(_size)
{
}

Worker::~Worker()
{
}

void Worker::Run()
{
	std::cout << "Worker with rank " << this->rank << " out of " << this->size << "\n";

	int line_size = hashes.size();
	MPI_Bcast(&line_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

	hashes.resize(line_size);

	MPI_Bcast(const_cast<char *>(hashes.data()), line_size, MPI_CHAR, 0, MPI_COMM_WORLD);

	std::map<std::string, std::string> cache;

	auto word = this->GetNextWord();
	// std::cout << word << " " << this->GetWordSalt(word) << std::endl;

	for (auto password_size = 1; password_size <= 8; password_size++)
	{
		this->InitializeIndex(password_size);
		auto password = this->GenerateNextPassword(password_size);

		cache.clear();

		this->hashesIndex = 0;

		while (this->hashesIndex < this->hashes.size())
		{
			auto hash = GetNextWord();

			auto salt = this->GetWordSalt(hash);

			std::string password_hash;

			if (cache.count(salt) > 0)
			{
				password_hash = cache[salt];
			}
			else
			{
				password_hash = std::string(crypt(password.c_str(), salt.c_str()));
			}

			if (password.compare("55") == 0)
			{
				std::cout << "AISOsajdouiahjoiadajsoiadjasj\n";
			}

			std::cout << "Testing password " << password << " with hash " << password_hash << " " << salt << " (" << this->rank << ")" << std::endl;
			if (password_hash.compare(hash) == 0)
			{
				std::cout << "EUREKAAAAAAAAAAAAAA " << password << " is " << password_hash << std::endl;
			}

			this->passwordsIndex++;
		}
		std::cout << " FINISHED! \n";
	}

	// while (true)
	// {
	// 	if (Master::oi != 0)
	// 	{
	// 		std::cout << "Killing worker" << std::endl;
	// 		for (auto i = 0; i < 1000; i++)
	// 		{
	// 		}
	// 		break;
	// 	}
	// }
}

void Worker::InitializeIndex(int size)
{
	unsigned long long int totalSenhas = pow(65, size); // Tamanho dicionario
	unsigned long long int indexesPerJob = totalSenhas / this->size;
	unsigned long long int startingIndex = this->rank * indexesPerJob;

	this->passwordsIndex = startingIndex;
}

std::string Worker::GenerateNextPassword(int size)
{
	// TIRAR ISSO DAQUI DEPOIS

	std::stringstream password;

	this->ConvertBase(passwordsIndex, 65, &password);

	return password.str();
}

std::string Worker::GetWordSalt(std::string word)
{
	return word.substr(0, 2);
}

std::string Worker::GetNextWord()
{
	this->hashesIndex;
	std::stringstream result;

	auto wordSize = 13;

	for (auto i = this->hashesIndex; i < this->hashesIndex + wordSize; i++)
	{
		result << this->hashes[i];
	}

	this->hashesIndex += wordSize;

	return result.str();
}

void Worker::ConvertBase(unsigned long long int index, int base, std::stringstream *s)
{
	static const auto dicionario = " ./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	if (index == 0)
		*s << dicionario[0];
	else
	{
		unsigned long long int value = index % base;
		*s << dicionario[value];
		this->ConvertBase(index / base, base, s);
	}
}