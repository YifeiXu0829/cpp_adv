#include <iostream>
#include <memory>


template<typename T>
class A
{
    public:
        
        A() = default ;
        ~A() = default;
        A(T v):value_(v)
        {
            //std::cout<<"user-defined constructor is called \n";
        }
        
        A(const A&) = delete;
       
        A(A& copy)
        {
            value_ = copy.value_;
            std::cout<<"copy constructor is called \n";
        }
        
        A(A&& copy)
        {
            value_ = copy.value_;
            std::cout<<"move constructor is called \n";
        }
        
        /* what is this called ???
        A(T&& v):value_(std::move(v))
        {
            std::cout<<" a weird constructor is called \n";
        }
        */

        A& operator=(const A& copy)
        {
            value_ = copy.value_;
            std::cout<<"copy assignment is called \n";
            return *this;
        }

        A& operator=(A&& copy)
        {
             value_ = copy.value_;
             std::cout<<"move assignment is called \n";
             return *this;
        }


    public:
        T value_;
};


template<typename T>
A<T> f(T a)
{
    return A<T>(a);
}


int main()
{
    int test = 567;
    //A<int> a = A<int>(123);
    //A<int> b = f(test);
    //A<int> c = a; //  copy c-tor
    //A<int> d;
    //d = a; // copy assignment
    std::cout<<"\n";
    A<int> pleasework = f(test);
}
