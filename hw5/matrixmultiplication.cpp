#include <iostream>
#include <vector>
#include <map>
#include <future>
#include <thread>
#include <algorithm>
double helper(std::map<int,double>& mat,std::vector<double>& v)
{
    double ret=0;

    //std::cout<<std::this_thread::get_id()<<std::endl;
    for(auto it=mat.begin();it!=mat.end();++it)
    {
        if(it->first <= v.size())
        {
            //std::string s= std::to_string(ret) + " =+" + std::to_string(v[it->first-1]) + " * " + std::to_string(it->second);
            //std::cout<<s<<" ---- "<<std::this_thread::get_id()<<std::endl;
            ret += v[it->first-1]*it->second;
        }
    }

    return ret;
}

auto pcalc(std::vector<std::map<int,double>>& mat, std::vector<double>& v)
{
    auto ret = std::vector<std::future<double>>();
    for(auto it=mat.begin();it!=mat.end();++it)
    {
        //std::future<double> ans = std::async(helper,*it,v);
        ret.emplace_back(std::async(std::launch::async,helper,ref(*it),ref(v)));
    }
    return ret;
}

int main()
{
    ///////// Prepare Test ///////////////////////
    std::vector<std::map<int,double>> mat;
    mat.emplace_back();
    mat.back().insert(std::make_pair(2,12.3));
    mat.back().insert(std::make_pair(3,.1));
    mat.emplace_back();
    mat.back().insert(std::make_pair(1,5));
    mat.emplace_back();
    mat.back().insert(std::make_pair(3,2.5));

    std::vector<double> densev{2,1.1,0};
    ///////////////////////////////////////////////


    ////////// async -> future ////////////////////
    auto res = pcalc(mat,densev);

    for(auto it=res.begin();it!=res.end();++it)
    {
        std::cout<< it->get() <<' ';
    }

    std::cout<<std::endl;



    ///////// Parallel Algorithm ///////////////////
    std::vector<double> res_pa(mat.size(),0);
    int index = 0;
    for(auto it=mat.begin();it!=mat.end();++it)
    {

        std::for_each(it->begin(),it->end(),[&](std::pair<int,double> pair)
                {
                    //std::cout<<pair.first<<" "<<pair.second<<std::endl;
                    res_pa[index] += densev[pair.first-1] * pair.second;
                }
        );
        ++index;
    }

    for(auto it=res_pa.begin();it!=res_pa.end();++it)
    {
         std::cout<< *it <<' ';
    }
    std::cout<<std::endl;

}
