#include <iostream>

#include <vector>
using namespace std;
class A
{
public:
    A(int val)
    {
        _val = val;
    }

    int GetVal() { return _val; }
private:
    int _val;
};

void MyFunc(unique_ptr<A> arg)
{
    cout << arg->GetVal() << endl;
}

int main(int argc, char* argv[])
{
    unique_ptr<A> ptr = unique_ptr<A>(new A(1234));
    MyFunc(move(ptr));
    assert(ptr == nullptr);
}
