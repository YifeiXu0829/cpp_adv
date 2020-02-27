#include <future>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <cassert>
using namespace std::chrono_literals;
///////////////////////////////////////////////////////  Imp /////////////////////////////////////////////
template<typename Func, typename ... Args>
auto my_async(Func&& f, Args ... args)
{
    std::packaged_task<typename std::result_of<Func(Args...)>::type(Args...)> task(std::forward<Func>(f));
    auto ret = task.get_future();
    std::thread my_thread(std::move(task), std::forward<Args>(args)...);
    my_thread.detach();
    //task(std::forward<Args>(args)...);
    
    return ret;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

int test3(int a, int b)
{
    std::this_thread::sleep_for(5s);
    assert(false && "oops, i did it on purpose!");
    return a+b;
}

template<class ...Args>
void test(Args&&... args)
{
   std::thread t(test3, std::forward<Args>(args)...);
    t.join();
}

int dummytest(double d, std::string s, std::vector<char>&& v)
{
    std::this_thread::sleep_for(2s);
    return (int)d + s.size() + v.size();
}

int f(int x, int y) { return std::pow(x,y); }

int main() {
    
    auto lambda1 = [](std::string_view s, int n) -> std::string{
        std::string ret = "";
        for (int i=0; i<n; ++i)
        {
            ret += s;
        }
        return ret;
    };
 /*   
    auto lambda2 = []() -> std::string{
        std::string ret = "test";
        
        return ret;
    };
    
    auto lambda3 = [](int a, int b) -> int{
        return a+b;
    };
*/ 
    std::string temp  = "hello ";
    std::string_view v = "hi ";
    int times = 5;
    auto fi1 = my_async(lambda1,v,times);
    std::cout<<"finish async 1"<<std::endl;
    auto fi2 = my_async(&dummytest,9.41341,std::move(temp),std::vector<char>{'a','b','c'});
    std::cout<<"finish async 2"<<std::endl;
    int one = 1;
    int two =2;
    auto fi3 = my_async(test3,std::move(one),std::move(two));
    std::cout<<"finish async 3"<<std::endl;
    //std::cout<<one<<" "<<two<<" \n";
    //auto fi3 = my_async(lambda3,1,2);
    
    std::cout<<"fi1 = "<< fi1.get()<<std::endl;
    std::cout<< "fi2 = "<< fi2.get()<<std::endl;
    std::cout<< "fi3 = "<< fi3.get()<<std::endl;
    
}
