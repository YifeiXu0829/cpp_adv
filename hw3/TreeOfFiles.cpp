#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <algorithm>

class Node
{
    public:
        Node():name_(""){}
        Node(std::string n):name_(n){}
        ~Node(){}
        std::string name_;
        std::vector<std::unique_ptr<Node>> nodes_;
};

void insertNode(std::unique_ptr<Node>* root, std::vector<std::string>& tokens)
{    
    for(int i=1;i<tokens.size();++i)
    {
        bool isfound = false;
        std::string name = tokens[i];
        std::vector<std::unique_ptr<Node>>& nodes = (*root)->nodes_;
        // if current token exists in subtree node
        for(auto it=nodes.begin();it!=nodes.end();++it)
        {
            if((*it)->name_ == name)
            {
                root = &(*it);
                isfound = true;
                break;
            }
        }
        
        if(!isfound)
        {
            // make a new node in vector nodes
            std::unique_ptr<Node> node = std::make_unique<Node>(name);
            nodes.push_back(std::move(node));
            //std::cout<<"New node : "<<name<<" created"<<std::endl;
        }  
    }
}

class PathsToTree
{
    public:
        PathsToTree(std::string file):filename_(file),isinit_(false)
        {
        }
        void readfile()
        {
            std::ifstream file("paths.txt");
            if(file.is_open())
            {
                std::string line="";
                std::vector<std::string> tokens;
                while(getline(file,line))
                {
                    //std::cout<<"line: "<<line<<std::endl;
                    tokens.clear();
                    // fill tokens
                    int start = 0;
                    int found = line.find_first_of('/',start);
                    while(found != std::string::npos)
                    {
                        tokens.push_back(line.substr(start,found-start));
                        start = found + 1;
                        found = line.find_first_of('/',start);
                    }
                    tokens.push_back(line.substr(start));
                    for(auto it=tokens.begin();it!=tokens.end();++it)
                    {
                        //std::cout<<*it<<" ";
                    }
                    //std::cout<<std::endl;

                    
                    // fill tree
                    if(tokens.size()==1)
                    {
                        if(!isinit_)
                        {
                            initroot(tokens[0]);
                            isinit_ = true;    
                        }
                    }
                    else if(tokens.size() > 1)
                    {
                        insertNode(&root_,tokens);
                    }
                    
                }
            }
        }
        void print()
        {

        }
    private:
        std::string filename_;
        std::unique_ptr<Node> root_;
        bool isinit_;
        void initroot(std::string name)
        {
            root_ = std::make_unique<Node>(name);
        }
};

int main()
{
    PathsToTree ob("paths.txt");
    ob.readfile();
    ob.print();
}
