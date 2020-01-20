#include <vector>

class PascalTriangle
{
 public:
    PascalTriangle(int lines):lines_(lines),bricksize_(0)
    {
        pascal();
    }
    ~PascalTriangle(){};
    void print();
 private:
    int lines_;
    int bricksize_;
    std::vector<std::vector<int>> map;
    void pascal();
    
};
