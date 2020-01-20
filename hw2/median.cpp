#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
using namespace std::chrono;

double median_sort(std::vector<double>& grades) // intro sort: O(nlgn) 
{
    std::sort(grades.begin(),grades.end());
    int l = grades.size();
    return l&1?grades[l/2]:(grades[l/2]+grades[l/2-1])/2;
}

double median_partialsort(std::vector<double>& grades) // cppreference says heapsort O(nlgm) so theoretically it should be faster than regular sort median since O(nlgn) > O(nlgm) (m=n/2 in this case) but practical result shows much worse than intro sort median search.
{
    int l = grades.size();
    std::partial_sort(grades.begin(),grades.begin()+l/2+1,grades.end());
    return l&1?grades[l/2]:(grades[l/2]+grades[l/2-1])/2;
}

double median_nthsort(std::vector<double>& grades) // Linear complexicity O(n) from cppreference.com which matches our practical speed tests result below.
{
    int l = grades.size();
    if(l&1)
    {
        std::nth_element(grades.begin(),grades.begin()+l/2,grades.end());
        return grades[l/2];
    }
    else
    {
        std::nth_element(grades.begin(),grades.begin()+l/2,grades.end());
        double a = grades[l/2];
        std::nth_element(grades.begin(),grades.begin()+l/2-1,grades.end());
        double b = grades[l/2-1];
        return (a+b)/2;
    }
}

template<typename T>
double median_sort_template(std::vector<T>& grades)
{
    std::sort(grades.begin(),grades.end());
    int l = grades.size();
    return l&1?grades[l/2]:(grades[l/2]+grades[l/2-1])/2;
}

int main()
{
    std::vector<double> test1 = {1.1,1.2,1.3,1.4,1.5};
    std::vector<double> test2 = {1.1,1.2,1.3,1.4};
    //std::cout<<"test1 median="<<median_partialsort(test1)<<" test2 median="<<median_partialsort(test2)<<std::endl;


    std::cout<<"preparing with 30 million samples, give it like 5 seconds."<<std::endl;
    std::vector<double> test_speed1;
    std::vector<double> test_speed2;
    std::vector<double> test_speed3;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    int test_size = 10000002; // 10 millions
    for (int n = 0; n < test_size; ++n) {
        double r = dis(gen);
        test_speed1.push_back(r); // initilize test samples
        test_speed2.push_back(r);
        test_speed3.push_back(r);
    }

    std::cout<<"testing with 10 million samples for each algorithm, give it like 15 seconds."<<std::endl;

    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    milliseconds start1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    result1 = median_sort_template(test_speed1);
    milliseconds end1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    milliseconds start2 = duration_cast<milliseconds>(system_clock::now().            time_since_epoch());
    result2 = median_partialsort(test_speed2);
    milliseconds end2 = duration_cast<milliseconds>(system_clock::now().          time_since_epoch());

    milliseconds start3 = duration_cast<milliseconds>(system_clock::now().              time_since_epoch());
     result3 = median_nthsort(test_speed3);
     milliseconds end3 = duration_cast<milliseconds>(system_clock::now().                time_since_epoch());

    if(result1 == result2 && result2==result3)
    {
        std::cout<<"with "<<test_size<<" sample size speed test:"<<std::endl;
        std::cout<<"regular sort median takes "<<(int64_t)(end1-start1).count()<<" ms"<<std::endl;
        std::cout<<"partial sort median takes "<<(int64_t)(end2-start2).count()<<" ms"<<std::endl; // practical result shows regular sort median is faster than partial_sort median 
        std::cout<<"nth_element sort median takes "<<(int64_t)(end3-start3).count()<<"  ms"<<std::endl; // practical result shows nth_element sort for median search is the fastest among the 3 methods listed.
    }
}
