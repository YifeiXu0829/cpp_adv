#include <iostream>
#include <mutex>
#include <memory>
#include <iostream>

template<typename T> class Node
{
    public:
        Node(T v):value_(v),next_(nullptr){};
        ~Node() = default;
        T value_;
        std::unique_ptr<Node> next_;
};

template<typename T> class Stack
{
    public:
        Stack ():size_(0),head_(nullptr)
        {

        }
        ~Stack() = default;
        void push(T a)
        {
            const std::lock_guard<std::mutex> lock(mutex_);
            std::unique_ptr<Node<T>> node = std::make_unique<Node<T>>(a);
            node->next_ = std::move(head_);
            head_ = std::move(node);
            ++size_;
        }
        /* [[nodiscard]] */ void pop()
        {
            const std::lock_guard<std::mutex> lock(mutex_);
            if(size_)
            {
                //T ret = head_->value_;
                head_ = std::move(head_->next_);
                --size_;
                //return ret;
            }
            //return -1;
        }
    private:
        int size_;
        std::mutex mutex_;
        std::unique_ptr<Node<T>> head_;
};



int main()
{
}
