#include "optimized_copy_if.h"
#include <iterator>
#include <iostream>
using namespace std;
using namespace mpcs;

int
main()
{
  int array[] = { 1, 2, 3, 4, 5 };
  int dest_array[5];
  optimized_copy(begin(array), end(array), dest_array);
  cout << "Print destination array to prove we copied" << endl;
  for (int i : dest_array)
    optimized_copy(begin(dest_array), end(dest_array), ostream_iterator<int>(cout, ", "));
  return 0;
}