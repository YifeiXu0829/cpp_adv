#include <iostream>
#include <vector>
#include "LockFreeStack.h"
using std::cout;
using std::endl;


int main(int argc, char* argv[])
{
    mpcs51044::Stack mystack;
    mystack.push(1);
    mystack.push(2);
    mystack.push(3);
    mystack.pop();
    mystack.pop();
    
}
