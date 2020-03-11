#ifndef btree_h
#  define btree_h
// Adapted from http://www.cprogramming.com/tutorial/lesson18.html 
// 1. Owning pointers become unique_ptr
// 2. node moved inside btree
// 3. Get rid of destructor and destroy_tree because cleanup is
//    automatically managed by RAII
// 4. Make search() const
// 5. Make search return a bool to encapsulate nodes away from user
// 6. Constructors don't need to null pointers any more. That is handled
//    by unique_ptr<>'s constructor]
// 7. Add namespace and include guard
// 8. Add copy constructor and assignment operator that
//    deep copy
// 9. Add move constructor and move assignment that shallow copy

#include<memory>
#include<utility>
using std::unique_ptr;
using std::make_unique;

namespace mpcs51044 {

class btree
{
    public:
		btree() { }

		// Copy construction and assignment deep copy
		btree(btree const &other) {
			if (other.root)
				root = make_unique<node>(*other.root);
		}
		btree &operator=(btree const &other) {
			if(&other != this) // Do nothing if self-assignment
				if(other.root)
					root = make_unique<node>(*other.root);
			return *this;
		}

		// Move construction and assignment shallow copy. See lecture notes
		btree(btree &&other) = default; // implicitly noexcept
		void operator=(btree &&other) noexcept { swap(root, other.root); }

		void insert(int key) {
			if (root)
				insert(key, root.get());
			else
			{
				root = make_unique<node>();
				root->key_value = key;
			}
		}
		bool search(int key) const {
			return search(key, root.get());
		}

    private:
		struct node
		{
			node() {}
			node(node const &other) : key_value(other.key_value) {
				if (other.left)
					left = make_unique<node>(*other.left);
				if (other.right)
					right = make_unique<node>(*other.right);
			}
			node &operator=(node const &other) {
				key_value = other.key_value;
				if (other.left)
					left = make_unique<node>(*other.left);
				if (other.right)
					right = make_unique<node>(*other.right);
				return *this;
			}
			int key_value;
			unique_ptr<node> left;
			unique_ptr<node> right;
		};

		void insert(int key, node *leaf) {
			if (key< leaf->key_value)
			{
				if (leaf->left != NULL)
					insert(key, leaf->left.get());
				else
				{
					leaf->left = make_unique<node>();
					leaf->left->key_value = key;
				}
			}
			else if (key >= leaf->key_value)
			{
				if (leaf->right != NULL)
					insert(key, leaf->right.get());
				else
				{
					leaf->right = make_unique<node>();
					leaf->right->key_value = key;
				}
			}
		}
		bool search(int key, node *leaf) const {
			if (leaf)
			{
				if (key == leaf->key_value)
					return leaf;
				if (key<leaf->key_value)
					return search(key, leaf->left.get());
				else
					return search(key, leaf->right.get());
			}
			else return false;
		}

		unique_ptr<node> root;
};
}
#endif




