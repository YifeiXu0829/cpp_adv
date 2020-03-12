#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/set.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <string>
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;
using namespace boost::interprocess;
int main(int argc, char* argv[])
{
    typedef allocator<int, managed_shared_memory::segment_manager>  ShmemAllocator;
    typedef set<int, std::less<int>,ShmemAllocator> set_type;

    if(argc == 1)
    {
        shared_memory_object::remove("SharedMemory"); // remove if SharedMemory exists

        managed_shared_memory segment(create_only, "SharedMemory", 65536);

        const ShmemAllocator alloc_inst (segment.get_segment_manager());
        set_type* myset = segment.construct<set_type>("test_set_boost_interprocess")(alloc_inst);
        
        myset->insert(1);
        myset->insert(3);
        myset->insert(2);

        // launch child process
        std::string command = std::string(argv[0]) + " childprocess";
        std::system(command.c_str());


        shared_memory_object::remove("SharedMemory");
    }
    else
    {
        // child process
        managed_shared_memory segment(open_only, "SharedMemory");
        set_type* myset = segment.find<set_type>("test_set_boost_interprocess").first;
        for(auto it=myset->begin();it!=myset->end();++it)
        {
            cout<<*it<<" ";
        }
        cout<<endl;
    }
}
