#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <chrono>

using std::cout;
using std::endl;
using namespace std::chrono_literals;

template<typename T>
class my_future
{
    public:
        my_future(){
            ready = false;
        }
        ~my_future(){}
        std::mutex cv_m;
        std::condition_variable cv;
        my_future(my_future& c) = delete;
        my_future& operator= (my_future& c) = delete;
    
        //my_future(my_future&& c) noexcept = default;
        //my_future& operator= (my_future&& c) = default;
    
        void set_value_state(T v, bool b=true)
        {
            ret = v;
            ready = b;
        }

        T get()
        {
            std::unique_lock<std::mutex> lk(cv_m);
            cv.wait(lk,[this]{return ready;}); // it did not block calling thread ... WHY ? T_T
            std::cout<<"start processing"<<endl;
            return ret;
        }
    private:
        T ret;
        bool ready;
        
};

template<typename R>
class my_promise
{
    public:
        my_promise()
        {
            future_ = std::make_shared<my_future<R>>();
        }
        ~my_promise(){}
        my_promise(my_promise& copy) = delete;
        my_promise& operator= (my_promise& copy) = delete;
        auto get_future()
        {
            return future_;
        }
    
        void set_value(R v)
        {
            std::lock_guard<std::mutex> lk(future_->cv_m);
            future_->set_value_state(v);
            future_->cv.notify_all();
        }
    
    private:
        std::shared_ptr<my_future<R>> future_;
};

void test1(int sec, my_promise<int>& p)
{
    cout<<"timer starts\n";
    std::this_thread::sleep_for(std::chrono::seconds(sec));
    cout<<"timer ends"<<endl;
    p.set_value(sec);
}

int main() {
    my_promise<int> test_promise1;
    auto future = test_promise1.get_future();
    std::thread testt1(test1,10,std::ref(test_promise1));
    //cout<<future.get()<<endl;
    testt1.detach();
    cout<<"what do we get: "<<future.get()<<endl;
    return 0;
}
