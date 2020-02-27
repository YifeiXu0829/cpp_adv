#include <future>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

#include <cassert>
using namespace std::chrono_literals;

// Use std::promise to create your own implementation of std::packaged_task

template <typename> class My_Packaged_Task;

template<typename R, typename ... Args>
class My_Packaged_Task<R(Args...)>
{
    public:
	    template <typename F>
	    explicit My_Packaged_Task(F&& f):func_(std::forward<F>(f))
        {
            //func_ = std::forward<F>(f);
	    }
        
        template<>
        My_Packaged_Task(My_Packaged_Task&) = delete;

        template<typename R1, typename ... Args1> // WHY ????? What the hell happened !???
        My_Packaged_Task& operator= (My_Packaged_Task&) = delete;

        auto get_future()
        {
            return p_.get_future();
        }

        void operator()(Args&& ... args)
        {
            auto res = func_(std::forward<Args>(args)...);
            p_.set_value(res);
        }
    private:
        std::promise<R> p_;
        std::function<R(Args...)> func_;
        
};

int test1(int a, int b)
{
    std::this_thread::sleep_for(5s);
    return a+b;
}
/*
double test2(std::string_view view, double f)
{
    std::this_thread::sleep_for(10s);
    return view.size() * f;
}
*/

int f(int x, int y) { return std::pow(x,y); }

int main()
{
    My_Packaged_Task<int(int,int)> mytask1(&test1);
    auto result1 = mytask1.get_future();

    auto lambda = [](std::string_view view, double f) -> double{
        std::this_thread::sleep_for(10s);
        return view.size() * f;
    };

    My_Packaged_Task<double(std::string_view,double)> mytask2(lambda);
    auto result2 = mytask2.get_future();
    std::string_view view= "this is a view";

    std::thread t1(std::move(mytask1),2,3);
    t1.detach();
    std::thread t2(std::move(mytask2),view,3.14);
    t2.detach();

    std::cout<<result1.get()<<std::endl;
    std::cout<<result2.get()<<std::endl;
    
    My_Packaged_Task<int()> task(std::bind(f, 2, 11));
    std::future<int> result = task.get_future();
 
    task();
 
    std::cout << "task_bind:\t" << result.get() << '\n';

	return 0;
}
