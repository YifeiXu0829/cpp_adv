#include <iostream>
#include <memory>
#include <cassert>
using namespace std;

template<typename T>
class Node
{
    public:
        Node(T k):key(k),left(nullptr),right(nullptr)
        {
        }
        ~Node() = default;
        Node(const Node&) = delete;
        Node& operator= (const Node&) = delete;
        T key;
        unique_ptr<Node> left; //child should only be owned by its parent, so delete Node copy constructor
        unique_ptr<Node> right; 

};

template<typename T>
class BTree
{
    public:
        BTree():root(nullptr)
        {
        }

        ~BTree() = default;

		BTree(const BTree& ) = delete; // Since we have a unique_ptr root so this should be implicitly deleted anyway.
		BTree& operator= (const BTree&) = delete; // so does this

        bool insert(T key)
        {
           if(root == nullptr)
           {
               root = make_unique<Node<T>>(key);
               return true;
           }
           else
           {
                return insert(key,root);
           }
        }
    
        bool insert(T key, unique_ptr<Node<T>>& node)
        {
            if(!node)
            {
                node = make_unique<Node<T>>(key);
                return true;
            }
            
            if(key == node->key)
            {
                return false;
            }
            else
            {
                return key > node->key ? insert(key,node->right) : insert(key,node->left);
            }
        }
    
        void print()
        {
            print(root);
        }
    
        void print(unique_ptr<Node<T>>& node)
        {
            if(!node) return;
            print(node->left);
            cout<<node->key<<" ";
            print(node->right);
        }

        auto search(T key)
        {
			if(root == nullptr)
            {
                return false;
            }
            else
            {
                 return search(key, root);
            }
        }
    
        auto search(T key, unique_ptr<Node<T>>& node)
        {
            if(!node) return false;
            if(node->key == key)
            {
                return true;
            }
            else
            {
                return node->key < key ? search(key,node->right) : search(key,node->left);
            }
        }
    
        auto remove(T key)
        {
            if(search(key)) // make sure it is in the tree.
            {
                remove(key,root);
                return true;
            }
            else
            {
                return false;
            }
            
        }
    
        void remove(T key, unique_ptr<Node<T>>& node)
        {
            if(key == node->key)
            {
                // this is the node to be removed
                // if there is no left child, replace this with it's right child
                if(!node->left)
                {
                    node = std::move(node->right);
                    return;
                }
                
                // o/w find it's left child tree's right most leaf and replace it with removed node.
                unique_ptr<Node<T>>* temp = &node->left; // here we use raw pointer to trace its right most child but not storing it thus the raw pointer has nothing with ownership.
                
                if(!(*temp)->right) // left child has no right children
                {
                    //unique_ptr<Node<T>>* tempright = &node->right;
                    (*temp)->right = std::move(node->right);
                    node = std::move(node->left);
                    return;
                }
                
                // find it's right most leaf
                while((*temp)->right)
                {
                    temp = &(*temp)->right;
                }
                
                //temp points to the node to replace current node
                node->key = (*temp)->key;
                (*temp).reset();
            }
            else
            {
                key > node->key ? remove(key, node->right):remove(key,node->left);
            }
        }
    

// Pros
// we will not need to implement Destroy tree because of RAII feature of using smart pointers.


    private:
        unique_ptr<Node<T>> root; 
};



int main()
{
    BTree<int> mytree;
    mytree.insert(2);
    mytree.insert(7);
    mytree.insert(5);
    mytree.insert(6);
    mytree.insert(3);
    mytree.insert(4);
    mytree.insert(1);
    mytree.insert(0);
    
    mytree.print();

	if(!mytree.search(6) || !mytree.search(0) || mytree.search(1989))
	{
		cout<<"something's wrong Yifei\n";
	}

    cout<<endl;

	mytree.remove(5);
    mytree.remove(3);

	if(mytree.search(5) || mytree.search(3))
    {
          cout<<"something's wrong Yifei\n";
    }
    mytree.print();
    //BTree<int> copy = mytree;
    //copy.print();

    return 0;
}
