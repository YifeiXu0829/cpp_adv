#include <iostream>
#include <memory>



class A
{
    public:
        
        A()
        {
            //std::cout<<"default c-tor is called\n";
        }
        ~A() = default;
        A(A&)// = delete;
        {
            std::cout<<"copy c-tor is called\n";
        }
        A(A&& copy)
        {
            std::cout<<"move c-tor is called\n";
        }

        A& operator=(A& copy)
        {
            std::cout<<"copy assignment is called\n";
            return *this;
        }

        A& operator=(A&& copy)
        {
            std::cout<<"move assignment is called\n";
            return *this;
        }
};

A f()
{
    return A();
}

void swap(A& a1, A& a2)
{
    A temp = std::move(a1); // move c-tor
    a1 = std::move(a2); // move assignment
    a2 = std::move(temp); // move assignment
}

class B
{
    public:

        B()
        {
         //std::cout<<"default c-tor is called\n";
        }
        ~B() = default;
        B(B&) = delete;
        //{
         //std::cout<<"copy c-tor is called\n";
        //}
        B(B&& copy)
        {
         std::cout<<"move c-tor is called\n";
        }

        B& operator=(B& copy)
        {
         //std::cout<<"copy assignment is called\n";
         return *this;
        }

        B& operator=(B&& copy)
        {
         //std::cout<<"move assignment is called\n";
         return *this;
        }
};

int main()
{
    A a =f(); //---->  use "clang++ -std=c++11 -fno-elide-constructors move.cpp -o build/test" to build in order to turn of RVO for move constructor to work in this case !!!  <-----

    //A a_copy = a; will not compile since copy c-tor is deleted.
    //A a_move = std::move(a);

    B b; // default c-tor of B()

    ///Users/yifeix/git/cpp_adv/hw4/move.cpp:88:7: error: call to deleted constructor of 'B'
    //B b_copy = b; // will not compile since copy c-tor is deleted.
    //  ^        ~

    B b_move = std::move(b); // move c-tor
    A a1;
    A a2;

    swap(a1,a2);

    return 0;
}
