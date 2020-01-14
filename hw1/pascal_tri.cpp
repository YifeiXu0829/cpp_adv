#include <vector>
#include <iostream>

#include "build/config.h"

int pascal(std::vector<std::vector<int>>& map, int n) // n is the number of lines of Pascal's triangle
{
    if (n<=0)
    {
        map.clear();
        return 0;
    }
    int bricksize = 1;

    while(n > 1)
    {
        std::vector<int> nextline;
        std::vector<int>& lastline = map[map.size()-1];
        nextline.push_back(lastline[0]); // insert left most element
        for(int i=1;i<lastline.size();++i)
        {
            int num = lastline[i-1]+lastline[i];
            nextline.push_back(num); // insert all middles
            if(std::to_string(num).size() > bricksize)
            {
                bricksize = std::to_string(num).size();
            }
        }
        nextline.push_back(lastline[lastline.size()-1]); // insert right most element
        map.push_back(nextline);
        --n;
    }

    return bricksize;
}


int main() {

    //std::cout << "project name: " << PROJECT_NAME << " version: " << PROJECT_VER << std::endl;
    std::cout << std::endl;
    std::cout<< "what many lines do you want to print of a pascal's triangle?"<<std::endl;
    std::cout<<"(just let it be a POSITIVE NUMBER and save me some time ...)"<<std::endl;
    
    int LINES=0;
    std::cin>>LINES;
    std::vector<std::vector<int>> tris(1,std::vector<int>{1});
    int bricksize = pascal(tris,LINES)+2;  // default output 8 numbers of lines.
    std::vector<std::string> outputs;
    for(auto it=tris.begin();it!=tris.end();++it)
    {
        std::string line;
        for (auto it2=it->begin();it2!=it->end();++it2)
        {
            // insert number in the center of the brick
            std::string brick = "";
            std::string number = std::to_string(*it2);
            for(int i = 0; i< (bricksize-number.size())/2;++i)
            {
                brick += " ";
            }
            brick += number;
            for(int i = 0; i< bricksize-number.size() - (bricksize-number.size())/2;++i)
            {
                brick += " ";
            }

            line += brick;
        }

        // lay bricks
        outputs.push_back(line);
    }

    int maxlength = outputs[outputs.size()-1].size();
    for(int i=0;i<outputs.size();++i)
    {
        std::string line = outputs[i];
        //calc indentions for each line
        int indentl = (maxlength - line.size())/2;
        std::string indent = std::string(indentl,' ');
        std::cout<<indent<<line<<std::endl;
    }

    std::cout << std::endl;
}
