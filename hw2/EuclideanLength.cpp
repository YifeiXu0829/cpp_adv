#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <numeric>

double helper(double init, double d)
{
    return (init + d*d);
}

int main()
{
    std::vector<double> vec1 = {1.1,2.2,3.3,4.4,5.5,6.6};
    std::transform(vec1.begin(),vec1.end(),vec1.begin(),[](double d) -> double { return d*d; });
    double sum = 0;
    for(auto it : vec1)
    {
        std::cout<<it<<",";
        sum += it;
    }
    std::cout<<'\n';
    //std::cout<<sum<<std::endl;
    sum = std::accumulate(vec1.begin(),vec1.end(),(double)0);
    std::cout<<"Accumulated Sum = "<<sum<<std::endl;
    std::cout<<"Euclidean Length using accumulate = "<<std::sqrt(sum)<<std::endl;

    std::vector<double> vec2 = {1.1,2.2,3.3,4.4,5.5,6.6};
    sum = std::inner_product(vec2.begin(),vec2.end(),vec2.begin(),(double)0);
    std::cout<<"Euclidean Length using inner product = "<<std::sqrt(sum)<<std::endl;

    std::vector<double> vec3 = {1.1,2.2,3.3,4.4,5.5,6.6};
    sum = std::accumulate(vec3.begin(),vec3.end(),(double)0,helper);
    std::cout<<"Euclidean Length using accumulate with function pointer = "<<std::sqrt(sum)<<std::endl;
}
