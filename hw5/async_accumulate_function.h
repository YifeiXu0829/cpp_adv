#ifndef ASYNC_ACCUMULATE_H
#define ASYNC_ACCUMULATE_H
// From Anthony Williams C++ Concurrency book
#include <thread>
#include <future>
#include <vector>
#include <numeric>
namespace mpcs51044 {
template<class T> 
T accumulate_future_value(T t, std::future<T> &f)
{
	return t + f.get();
}

template<typename Iterator,typename T>
T async_accumulate(Iterator first,Iterator last,T init)
{
    unsigned long const length=std::distance(first,last);
    if(!length)
        return init;
    unsigned long const min_per_thread=25;
    unsigned long const max_threads = (length+min_per_thread-1)/min_per_thread;

    // hardware_concurrency may return 0 if it doesn't choose to answer
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads
       = std::min(hardware_threads!=0?hardware_threads:2,max_threads);
    unsigned long const block_size=length/num_threads;
    std::vector<std::future<T> > futures(num_threads-1);
    Iterator block_start=first;
    for(unsigned long i=0;i<(num_threads-1);++i) {
        Iterator block_end=block_start;
        std::advance(block_end,block_size);
        futures[i]
          = std::async(
			   std::accumulate<Iterator,T>,
			   // next line for MSVC 2010, instead of the above:
			   //static_cast<T (*)(Iterator, Iterator, T)>(std::accumulate<Iterator,T>),
               block_start,
               block_end,
               T{});
        block_start=block_end;
    }
	return std::accumulate
		     (futures.begin(),
			  futures.end(),
              std::accumulate(block_start, last, T()),
              [](auto &acc, auto &next) { return acc + next.get();  }
			  );
}

}
#endif
