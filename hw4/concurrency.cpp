#include <iostream>
#include <thread>
#include <memory>
#include <mutex>
#include <string>
#include <sstream>
std::mutex mutex_;

void _func_with_lock(int& counter)
{
    for(int i=0;i<100;++i)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout<<"Thread "<<std::this_thread::get_id() <<" has been called "<<++counter<<" times\n";
    }
}

void _func_without_lock(int& counter)
{
    for(;;)
    {
		std::stringstream ss;
		ss << std::this_thread::get_id();
		std::string mystring = ss.str();
		std::string s = "Thread " + mystring + " has been called " + std::to_string(++counter) + " times\n";
        std::cout<<s;  
	}
}

int main()
{
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;

	// with Lock
    //std::thread t1(_func_with_lock,std::ref(counter1));
    //std::thread t2(_func_with_lock,std::ref(counter2));
    //std::thread t3(_func_with_lock,std::ref(counter3));


	// without Lock !
	std::thread t1(_func_without_lock,std::ref(counter1));
    std::thread t2(_func_without_lock,std::ref(counter2));
    std::thread t3(_func_without_lock,std::ref(counter3));

    t1.join();
    t2.join();
    t3.join();
}

/* Submit the output from your program.
 *      See ouputs.txt
 *
 * What does it tell you about how threads are actually scheduled on your system?
 * It looks like system schedules tasks rather than threads. This process has 4 threads which are 
 * main thread, t1,t2,and t3. From the outputs, t1,t2 and t3 thread tasks interleaved with each other,
 * which means thread will wait on other threads if other threads has a higher priority task.
 */
