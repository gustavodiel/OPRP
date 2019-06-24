#pragma once

#include <string>
#include <sstream>

class Worker
{
protected:
	int size, rank;

	unsigned long long int passwordsIndex;

	std::string hashes;

public:
	Worker(int, int);
	~Worker();

	void Run();

    virtual std::string GetNextWord(int);
	std::string GenerateNextPassword();

    static inline void GetWordSalt(std::string&, char*);

protected:
    unsigned long long int InitializeIndex(int);

    void inline ConvertBase65(unsigned long long int, std::stringstream *);

    static inline unsigned long long int powerOf65(int power) {
        switch (power) {
            case 0: return 1ULL;
            case 1: return 65ULL;
            case 2: return 4225ULL;
            case 3: return 274625ULL;
            case 4: return 17850625ULL;
            case 5: return 1160290625ULL;
            case 6: return 75418890625ULL;
            case 7: return 4902227890625ULL;
            case 8: return 318644812890625ULL;
            case 9: return 20711912837890625ULL;
            default: return 0;
        }
    }

};
