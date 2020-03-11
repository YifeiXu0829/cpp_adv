#include "Format.h"
#include <iostream>
using namespace mpcs;
using std::cout;

int main()
{
    cout << format("id {} - name {}", 5, "Mike");
}