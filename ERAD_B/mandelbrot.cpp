#include <complex>
#include <iostream>
#include <omp.h>
#include <sstream>
#include <string>

using namespace std;

int main(){
	int max_row, max_column, max_n;
	cin >> max_row;
	cin >> max_column;
	cin >> max_n;

	char **mat = (char**)malloc(sizeof(char*) * max_row);

    char *temp = (char*)malloc(sizeof(char) * max_row * max_column);

    for (int i = 0; i < max_row; i++) {
      mat[i] = (i*max_column + temp);
    }

	int r;

#pragma omp parallel for num_threads(8) schedule(dynamic)
	for(r = 0; r < max_row * max_column; ++r){
		complex<float> z;
		int n = 0;

		int row    = (int)(r / max_column);
		int column = r % max_column;

		while(abs(z) < 2 && ++n < max_n)
			z = z * z + decltype(z)(
				(float)column * 2 / max_column - 1.5,
				(float)row * 2 / max_row - 1
			);

		(*mat)[r]=(n == max_n ? '#' : '.');
	}

	std::stringstream ss;

	for(int r = 0; r < max_row; ++r){
		for(int c = 0; c < max_column; ++c)
			ss << mat[r][c];
		ss << '\n';
	}

	std::cout << ss.str();
}
