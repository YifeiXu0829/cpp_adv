#include <iostream>
#include <mutex>
#include <memory>
#include <iostream>

template<typename T> class Node
{
    public:
        Node(T v):value_(v),next_(nullptr){};
        ~Node() = default;
    private:
        std::unique_ptr<Node> next_;
        T value_;
};

template<typename T> class Stack
{
    public:
        Stack ()
        {

        }
        ~Stack() = default;
        void push(T a)
        {
            const std::lock_guard<std::mutex> lock(mutex_);
        }
        /* [[nodiscard]] */ auto pop()
        {
            const std::lock_guard<std::mutex> lock(mutex_);
            return 0;
        }
    private:
        std::mutex mutex_;

};



int main()
{
    Stack<int> stack;
    int testsize = 10;
    for(auto i=0;i<testsize;++i)
    {
        stack.push(i);
        std::cout<<i<<" ";
    }

    std::cout<<std::endl;

    for(auto i=0;i<testsize;++i)
    {
        std::cout<<stack.pop()<<" ";
    }

    std::cout<<std::endl;
}
