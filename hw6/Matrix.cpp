#include "Matrix.h"
#include <iostream>
#include <chrono>
using namespace mpcs51044;
using namespace std;

int main()
{
	auto start = chrono::system_clock::now();
	Matrix<3, 3> m = { 
			{ 1, 2, 3, }, 
			{ 4, 5, 6, }, 
			{ 7, 8, 9, } 
	};

    Matrix<3, 3> test1 = {
            { 1, 2, 3, },
            { 4, 5, 6, },
            { 7, 8, 9, }
    };

    Matrix<3, 3> test2 = {
            { 7, 8, 9, },
            { 4, 5, 6, },
            { 1, 2, 3, }
    };

    std::cout<<test1+test2<<std::endl;
    test1 += test2;
    std::cout<<test1<<std::endl;
	static double total;
	for (int i = 0; i < 100'000'000; i++) {
		m(1, 1) = i;
		total += m.determinant();
	}
	cout << chrono::duration<double>(chrono::system_clock::now() - start).count() << " seconds\n";
}
