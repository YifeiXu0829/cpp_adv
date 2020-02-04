#include <iostream>
#include <mutex>
#include <memory>
#include <iostream>
#include <optional>

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
        void push(T a) noexcept
        {
            const std::lock_guard<std::mutex> lock(mutex_);
            std::unique_ptr<Node<T>> node = std::make_unique<Node<T>>(a);
            node->next_ = std::move(head_); // swap resrc between new node next and current head, thus current head points to null, and new node next points to pre head
            head_ = std::move(node); // swap between current head resrc and new node resrc, thus current head points to new node, and new node held current head's resrc which is null and will be destructed when new node goes out of scope.
            ++size_;
        }
        [[nodiscard]] std::optional<T> pop() noexcept
        {
            const std::lock_guard<std::mutex> lock(mutex_);
            if(size_)
            {
                T ret = head_->value_;
                head_ = std::move(head_->next_);
                --size_;
                return ret;
            }
            return {};
            // better check size before you pop
        }

        bool empty() noexcept // always do empty check before pop() !
        {
            return size_?0:1;
        }

        int size() noexcept
        {
            return size_;
        }

        [[nodiscard]] std::optional<T> back() noexcept
        {
               const std::lock_guard<std::mutex> lock(mutex_);
               if(size_)
               {
                   T ret = head_->value_;
                   return ret;
               }
               return {};
               // better check size before you back()
        }
    private:
        int size_;
        std::mutex mutex_;
        std::unique_ptr<Node<T>> head_;
};



int main()
{
    // how to realize unique_ptr to unique pointer ????
    
    Stack<std::string> stack;
    
    for(int i=0;i<10;++i)
    {
        stack.push(std::to_string(i));
        std::cout<<i<<" ";
    }

    std::cout<<std::endl;
    for(int i=0;i<11;++i)
    {
        if(!stack.empty())
        {
            std::optional<std::string> ret = stack.pop();
            if(ret.has_value())
            {
                std::cout<<*ret<<" ";
            }
            //std::cout<<stack.pop()<<" ";
        }
    }
    std::cout<<std::endl;
    
}
