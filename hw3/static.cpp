#include <iostream>
#include <memory>
class Test
{
    public:
        Test()
        {
            //std::cout<<"DEFAULT";
        }
        Test(int user){std::cout<<"Hel";}
        virtual ~Test(){std::cout<<"\n";} // called twice for two children during destruction
    private:

};

class SubTest1 : public Test
{
    public:
        SubTest1(int user):Test(user)
        {
            std::cout<<"lo";
        } 
        virtual ~SubTest1(){std::cout<<"World!";}
};

class SubTest2 : public Test
{
    public:
        SubTest2():Test()
        { 
            std::cout<<" Sub2 ";
        }
        SubTest2(SubTest1& copy){std::cout<<",";}
        virtual ~SubTest2(){std::cout<<" ";}
};

static std::unique_ptr<SubTest1> subtest1 = std::make_unique<SubTest1>(2);
static std::unique_ptr<SubTest2> copy = std::make_unique<SubTest2>(*subtest1);

int main()
{
    return 0;
}
