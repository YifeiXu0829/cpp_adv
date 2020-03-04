#include <range/v3/all.hpp>
#include <iostream>
#include <vector>

using namespace ranges;
using std::cout;
using std::endl;
int main()
{
    std::vector<double> v1{0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0};
    std::vector<double> v2;
    v2 = v1 | views::transform([](double d) 
            {
                return d*d;
            })
            | to<std::vector>()            
        ;

    for(auto& i : v1)
    {
        cout<<i<<" ";
    }

    cout<<endl;

    for(auto& i : v2)
    {
        cout<<i<<" ";
    }

    cout<<endl;
    //std::cout<<v2<<endl;
    return 0;
}
