#include "btree.h"
#include <iostream>
#include <algorithm>
using namespace mpcs51044;
using std::cout;
using std::swap;

void examine(btree const &t)
{
	for (int i = 0; i < 6; i++) {
		if (t.search(i))
			cout << "Contains " << i << "\n";
		else
			cout << "Does not contain " << i << "\n";
	}
}

btree f() {
	btree result;
	result.insert(0);
	result.insert(5);
	result.insert(2);
	examine(result);
	return result;
}
int main()
{
	btree t1{f()}; // Moves from temporary to avoid unnecessary copy
	btree t2(t1); // Deep copy
	t1.insert(3); // Won't effect t2
	cout << "t1:\n====\n";
	examine(t1);
	cout << "t2:\n====\n";
	examine(t2);
	swap(t1, t2); // Efficiently only swaps the roots using move construction 
	// Not creating a new object, but using assignment to modify an existing object, so
	// assignment operators (i.e., operator=) are used rather than constructors
	t2 = t1; // Copy assignment
	t2 = f(); // Move assignment
	return 0;
}