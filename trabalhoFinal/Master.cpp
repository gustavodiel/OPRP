#include "Master.hpp"

#include <iostream>
#include <map>
#include <cmath>
#include <iomanip>

#include <mpi.h>
#include <crypt.h>

#define HASH_SIZE 13


Master::Master(int size, int rank, std::string hashes) : Worker(size, rank), hashes(std::move(hashes))
{
}

Master::~Master()
{
}

void Master::Run()
{
	std::cout << "Master with rank " << this->rank << " out of " << this->size << "\n";

	int line_size = hashes.size();
	MPI_Bcast(&line_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(const_cast<char *>(hashes.data()), line_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    int passwordSize = 3;
    auto indexPerJob = powerOf65(passwordSize);
    this->passwordsIndex = 0;

    crypt_data data;
    data.initialized = 0;

    auto salt = new char(3);

    std::cout << "[" << std::setw(3) << this->rank << "] Going to process " << indexPerJob << " passwords (" << passwordSize << ")" << std::endl;

    int hashesSize = this->hashes.size();

    for (auto i = 0; i < indexPerJob; i++)
    {
        auto password = this->GenerateNextPassword();
        int lHashesIndex = 0;

        while (lHashesIndex < hashesSize)
        {
            std::string password_hash;
            auto hash = this->GetNextWord(lHashesIndex);
            GetWordSalt(hash, salt);

            lHashesIndex += HASH_SIZE;

            auto cryptHash = crypt_r(password.c_str(), salt, &data);

            if (!cryptHash)
            {
                std::cout << "NUUUUUUUUUUUUUUUUUUUULL [" << salt << "] [" << hash << "] " << this->hashes << std::endl;
            }

            password_hash = std::string(cryptHash);

            if (password_hash[3] == hash[3] && password_hash == hash)
            {
                std::cout << "[" << std::setw(3) << this->rank << "] EUREKAAAAAAAAAAAAAA \"" << password << "\" is " << password_hash << std::endl;
            }
        }
    }

}

std::string Master::GetNextWord(int hashesIndex)
{
    return this->hashes.substr(hashesIndex, HASH_SIZE);
}

void Master::GetWordSalt(std::string & word, char* salt)
{
    salt[0] = word[0];
    salt[1] = word[1];
    salt[2] = '\0';
}

