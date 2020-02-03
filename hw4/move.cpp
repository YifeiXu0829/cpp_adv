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
        A(A&) = delete;
        //{
            //std::cout<<"copy c-tor is called\n";
        //}
        A(A&& copy)
        {
            std::cout<<"move c-tor is called\n";
        }


        A& operator=(A& copy)
        {
            return *this;
        }
};

A f()
{
    return A();
}


int main()
{
    A a =std::move(f());
    //A a_copy = a; will not compile since copy c-tor is deleted.
    A a_move = std::move(a);

    return 0;
}
