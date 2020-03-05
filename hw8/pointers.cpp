#include <iostream>
#include <string>
#include <cmath>
using std::cout;
using std::endl;

class A
{
  public:
    A():value(0){}
    int value;
    //static int counter;
    int set_value(int* v)
    {
        value = *v;
        return value;
    }
    
    int latebind(double (*f)(float&))
    {
        float t = 1.5f;
        return std::ceil(f(t));
    }
    
    /*
    static int set_value_static(int* v)
    {
        counter = *v;
        return counter;
    }
    */
};

//int A::counter = 1;

double passingfunc (float& f)
{
    return (double)f;
}

int voidretint()
{
    return 666;
}

char* concat(char* a, char* b)
{
    std::string s = std::string(a) + b;
    
    char* ret = new char[strlen(a)+strlen(b)+1];
    std::strcpy(ret, s.c_str());
    return ret;
}



void test( void (*f) ())
{
    return;
}

int main() {
    int ar[5] = {0,1,2,3,4};
    int* a = ar;
    
    int p = 5;
    int& pr = p;

    A* classA = new A();
    
    char c = 'C';
    char const* cptr = &c;
    //*cptr = 's'; // compile error, you can not change what cptr points since that is a const
    char const& cr = c;
    // cr = 's';// compile error, you can not change what cr is referenced 
    
    long malloc7[7] = {0l,1l,2l,3l,4l,5l,6l};
    
    p = 5; // init above as an int
    int* iptr = &p;
    int** pp = &iptr; // points to the memory of a pointer that points to an integer
    
    int* &pref = iptr; // reference of a pointer
    
    float f = 0.05f;
    float& fref = f;
    
    int (*func)() = voidretint;
    cout<<func()<<endl;
    
    int (*&funcref)() = func; // reference of function pointer func
    cout<<func()<<endl;
    
    char* (*func2)(char*,char*) = concat;
    char* temp = concat("hello ","world");
    cout<<temp<<endl;
    delete[] temp;
    
    int A::* mptr = &A::value;
    cout<<classA->*mptr<<endl;
    
    int v = 8;
    int (A::*fA)(int*) = &A::set_value; // member function pointer
    cout<< (classA->*fA) (&v)<<endl;
    
    int (A::**ptrtofuncptr) (int *) = &fA; // a  pointer points to a member function pointer
    cout<<  (classA->*(*ptrtofuncptr)) (&v)<<endl;
    
    int (A::*&ptrtofuncref) (int *) = fA; // a reference to a member function pointer
    cout<<  (classA->*ptrtofuncref) (&v)<<endl;
    
    int (A::*mfunc) (double (*) (float&)) = &A::latebind;  // a member function pointer accepts a non-member function pointer as input argument
    cout<< (classA->*mfunc)(passingfunc)<<endl;
    
    void (*pa[10]) (void(*)()) = {test,test,test,test,test,test,test,test,test,test}; // an array of function point that accept a function pointer as input argument.
}
