#include <iostream>
using std::cout;
using std::endl;

template<class T,typename ... Args>
void my_print_impl(T& arg, Args ... args)
{
   cout << "lvalue reference" << endl;
}

template<class T, typename ... Args>
void my_print_impl(T&& arg, Args ... args)
{
   cout << "rvalue reference" << endl;
}

template<class T, typename ... Args>
void my_print(T&& arg, Args&& ... args)
{
    my_print_impl(std::forward<T>(arg), std::forward<T>(args)...);
}

int main()
{
    int i = 1;
    int & l_ref = i;
    int && r_ref = 1;
    my_print(l_ref);            //print lvalue reference
    my_print(r_ref);            //print lvalue reference
    my_print(std::move(l_ref)); //print rvalue reference
    my_print(1);                //print rvalue reference, 1 is a true rvalue
    my_print(i);

    return 0;
}
