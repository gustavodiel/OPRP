#include "Worker.hpp"

#include "Master.hpp"

#include <iostream>
#include <map>
#include <cmath>
#include <iomanip>

#include <mpi.h>
#include <crypt.h>
#include <omp.h>

#define to -- >

Worker::Worker(int _size, int _rank) : rank(_rank), size(_size), hashesIndex(0)
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
	// std::cout << this->hashes << std::endl;

	auto word = this->GetNextWord();
	// std::cout << word << " " << this->GetWordSalt(word) << std::endl;

	for (auto password_size = 2; password_size <= 8; password_size++)
	{
		auto indexPerJob = this->InitializeIndex(password_size);

		crypt_data data;
		data.initialized = 0;

		std::cout << "[" << std::setw(3) << this->rank << "] Going to process " << indexPerJob << " passwords (" << password_size << ")" << std::endl;

#pragma omp parallel for num_threads(6) private(data) shared(password_size) schedule(dynamic) nowait
		for (int i = 0; i < indexPerJob; i++)
		{
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
					password_hash = std::string(crypt_r(password.c_str(), salt.c_str(), &data));
				}

				// std::cout << "Testing password " << password << " with hash " << password_hash << " " << salt << " (" << this->rank << ")" << std::endl;
				if (password_hash.compare(hash) == 0)
				{
					std::cout << "[" << std::setw(3) << this->rank << "] EUREKAAAAAAAAAAAAAA " << password << " is " << password_hash << std::endl;
				}
			}
		}
	}
}

unsigned long long int Worker::InitializeIndex(int size)
{
	unsigned long long int totalSenhas = pow(65, size); // Tamanho dicionario
	unsigned long long int indexesPerJob = totalSenhas / (this->size - 1);
	unsigned long long int startingIndex = pow(65, size - 1) + (this->rank - 1) * indexesPerJob;

	this->passwordsIndex = startingIndex;

	return indexesPerJob;
}

std::string Worker::GenerateNextPassword(int size)
{
	// TIRAR ISSO DAQUI DEPOIS

	std::stringstream password;

	this->ConvertBase(this->passwordsIndex, 65, &password);
	this->passwordsIndex++;

	return password.str();
}

std::string Worker::GetWordSalt(std::string word)
{
	return word.substr(0, 2);
}

std::string Worker::GetNextWord()
{
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

	if (index < base)
		*s << dicionario[index];
	else
	{
		unsigned long long int value = index % base;
		*s << dicionario[value];
		this->ConvertBase(index / base, base, s);
	}
}
