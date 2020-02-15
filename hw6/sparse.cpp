#include"sparse.h"
#include<cassert>
#include<vector>
#include<iostream>
using namespace mpcs;
using namespace std;

int main()
{
	SparseMatrix sm;
	sm.push_back({ {1, 12.3}, {2, .1} });
	sm.push_back({ {0, 5} });
	sm.push_back({ {2, 2.5} });
	auto product = sm * vector<double>{2, 1.1, 0};
	cout << "(" << product[0] << ", " << product[1] << ", " << product[2] << ")\n";
	return 0;
}