#include <vector>
#include <numeric>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
using namespace std; // Don't do this in a job interview

typedef vector<int> Row;  // Tired and old-fashioned
using Triangle = vector<Row>; // Alternate notation for typedef

Row
nextRow(Row row)
{
    Row result;
    int previous = 0;
    for (auto elt : row) {
        result.push_back(previous + elt);
        previous = elt;
    }
    result.push_back(previous);
    return result;
}

// int const rows = 10; // Passe
int constexpr rows = 10;  // Do this now

int
numDigits(int i)
{
    int digits = 1;
    while ((i /= 10) != 0) {
        digits++;
    }
    return digits;
}

int
numDigits_alternate(int i)
{
    ostringstream os;
    os << i;
    return os.str().size();
}

int numDigits_alt2(int i)
{
    return std::to_string(i).size();
}

int eltSize;

string
centeredInt(int i)
{
    return string((eltSize - to_string(i).size()) / 2, ' ') + to_string(i);
}

void
printRow(ostream& os, Row row)
{
    for (auto elt : row) {
        os << left << setw(eltSize) << centeredInt(elt) << " ";
    }
    os << endl;
}

// This is type-unsafe! Triangle should be a class. HW 2.4 fixes
ostream&
operator <<(ostream& os, Triangle triangle)
{
    Row lastRow = triangle[rows - 1];

    int maxElement = *max_element(lastRow.begin(), lastRow.end());
    eltSize = numDigits(maxElement);
    for (int i = 0; i < rows; i++) {
        string spaces((rows - i - 1) * (eltSize + 1) / 2, ' ');
        os << spaces;
        printRow(os, triangle[i]);
    }
    return os;
}


int
main()
{
    Triangle triangle;
    Row previousRow = { 1 };
    for (int i = 0; i < rows; i++) {
        triangle.push_back(previousRow);
        previousRow = nextRow(previousRow);
    }
    cout << triangle;
    return 0;
}
