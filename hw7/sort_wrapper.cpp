#include <iostream>
#include <list>
#include <vector>
#include <type_traits>

template <typename InputIt>
void bad_sort(InputIt begin,InputIt end)
{
    std::sort(begin,end);
}

template <typename InputIt, std::enable_if_t<std::is_same<std::random_access_iterator_tag,typename std::iterator_traits<InputIt>::iterator_category>::value,int> = 0 >
void MySort(InputIt begin, InputIt end)
{
    /*
    using category = typename std::iterator_traits<InputIt>::iterator_category;
    if constexpr (!std::is_same_v<category, std::random_access_iterator_tag>)
    {
        static_assert(true && "this is not okay"); // this does not really help since the complier will still go compiling and produce more errors.
    }
    */
    std::sort(begin,end);
}

template <typename T, std::enable_if_t<std::is_integral<T>::value,int> = 0 >
void test(T t)
{
    std::cout<<t<<'\n';
}

int main()
{
    std::vector<int> v{3,2,1};
    std::list<int> l{4,3,2};
    MySort(v.begin(),v.end());
    //bad_sort(l.begin(),l.end()); // see compiler_error_SFINAE.txt for details of compiler error description.
    for(auto& i : v)
    {
        std::cout<<i<<std::endl;
    }

    MySort(l.begin(),l.end()); // using enable_if to generate a compiler error of mo matching callable is much more clean. Improvement: aside from the fact of easy error tracking from compiler output, using enable if makes the library safer to use, fixed the over-inclusive issue for template prototype.

    for(auto& i : l)
    {
        std::cout<<i<<std::endl;
    }

    //test("test");
}
