#include <range/v3/all.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace ranges;
using std::cout;
using std::endl;
int main()
{
    std::vector<double> v1{0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0};
    auto sum = inner_product(v1,v1,0.0);
    for(auto& i : v1)
    {
        cout<<i<<" ";
    }

    cout<<endl;

    std::cout<<std::sqrt(sum)<<endl;
    return 0;
}
