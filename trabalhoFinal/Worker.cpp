#include "Worker.hpp"

#include "Master.hpp"

#include <iostream>
#include <map>
#include <cmath>
#include <iomanip>

#include <mpi.h>
#include <crypt.h>
#include <omp.h>

#include "colors.hpp"

#define HASH_SIZE 13

Worker::Worker(int _size, int _rank) : rank(_rank), size(_size)
{
}

Worker::~Worker() = default;

void Worker::Run()
{
	int line_size = 0;
	MPI_Bcast(&line_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

	hashes.resize(line_size);

	MPI_Bcast(const_cast<char *>(hashes.data()), line_size, MPI_CHAR, 0, MPI_COMM_WORLD);
	int i, lRank = this->rank;

    int hashesSize = this->hashes.size();

    for (auto passwordSize = 4; passwordSize <= 8; passwordSize++)
	{
		const auto indexPerJob = this->InitializeIndex(passwordSize);

		crypt_data data;
		data.initialized = 0;

		std::cout << BOLDCYAN << "[" << BOLDRED << std::setw(6) << lRank << BOLDCYAN <<"] " << GREEN << "Going to process " << BOLDMAGENTA << indexPerJob << GREEN << " passwords (" << WHITE << "size of " << BOLDBLUE << passwordSize << GREEN << ")" << RESET << std::endl;

#pragma omp parallel num_threads(6) private(i, data) shared(passwordSize, lRank, hashesSize)
#pragma omp for schedule(dynamic)
		for (i = 0; i < indexPerJob; i++)
		{
			const auto password = this->GenerateNextPassword();
			int lHashesIndex = 0;

            char salt[3];

            while (lHashesIndex < hashesSize)
			{
				std::string password_hash;
				auto hash = this->GetNextWord(lHashesIndex);

				GetWordSalt(hash, salt);

				lHashesIndex += HASH_SIZE;

				auto cryptHash = crypt_r(password.c_str(), salt, &data);

				password_hash = std::string(cryptHash);

				if (password_hash[3] == hash[3])
				{
				    if (password_hash == hash) {
				    	std::cout << BOLDCYAN << "[" << BOLDRED << std::setw(6) << lRank << BOLDCYAN <<"]" << GREEN << " EUREKAAAAAAAAAAAAAA found password \"" << BOLDWHITE << password << GREEN << "\" of hash " << BOLDMAGENTA << password_hash << RESET << std::endl;
					}
				}
			}
		}
	}
}

unsigned long long int Worker::InitializeIndex(int passwordSize)
{
	unsigned long long int totalSenhas = powerOf65(passwordSize); // Tamanho dicionario
	unsigned long long int indexesPerJob = totalSenhas / (this->size - 1);
	unsigned long long int startingIndex = powerOf65(passwordSize - 1) + (this->rank - 1) * indexesPerJob;

	this->passwordsIndex = startingIndex;

	return indexesPerJob;
}

std::string Worker::GenerateNextPassword()
{
	std::stringstream password;

	this->ConvertBase65(this->passwordsIndex, &password);
	this->passwordsIndex++;

	return password.str();
}

void Worker::GetWordSalt(std::string & word, char* salt)
{
    salt[0] = word[0];
    salt[1] = word[1];
    salt[2] = '\0';
}

std::string Worker::GetNextWord(int hashesIndex)
{
	return this->hashes.substr(hashesIndex, HASH_SIZE);
}

void Worker::ConvertBase65(unsigned long long int index, std::stringstream *s)
{
	static const auto dicionario = " ./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	static const int base = 65;

	if (index < base)
		*s << dicionario[index];
	else
	{
		unsigned long long int value = index % base; /* index % base */
        *s << dicionario[value];
        this->ConvertBase65(index / base, s);
	}
}
