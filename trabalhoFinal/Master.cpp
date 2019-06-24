#include "Master.hpp"

#include <iostream>
#include <map>
#include <cmath>
#include <iomanip>

#include <mpi.h>
#include <crypt.h>

#include "colors.hpp"

#define HASH_SIZE 13


Master::Master(int size, int rank, std::string hashes) : Worker(size, rank), hashes(std::move(hashes))
{
}

Master::~Master()
{
}

void Master::Run()
{
	int line_size = hashes.size();
	MPI_Bcast(&line_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(const_cast<char *>(hashes.data()), line_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    int passwordSize = 3;
    const auto indexPerJob = powerOf65(1) + powerOf65(2) + powerOf65(3);
    this->passwordsIndex = 0;

    crypt_data data;
    data.initialized = 0;

    auto salt = new char(3);

    std::cout << BOLDCYAN << "[" << BOLDRED << "MASTER" << BOLDCYAN <<"] " << GREEN << "Going to process " << BOLDMAGENTA << indexPerJob << GREEN << " passwords (" << WHITE << "size of " << BOLDBLUE << "1, 2, and 3" << GREEN << ")" << RESET << std::endl;

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
                std::cout << BOLDRED << "NUUUUUUUUUUUUUUUUUUUULL [" << salt << "] [" << hash << "] " << this->hashes << RESET << std::endl;
            }

            password_hash = std::string(cryptHash);

            if (password_hash[3] == hash[3] && password_hash == hash)
            {
                std::cout << BOLDCYAN << "[" << BOLDRED << "MASTER" << BOLDCYAN <<"]" << GREEN << " EUREKAAAAAAAAAAAAAA found password \"" << BOLDWHITE << password << GREEN << "\" of hash " << BOLDMAGENTA << password_hash << RESET << std::endl;
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

