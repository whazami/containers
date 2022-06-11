#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include "pair.hpp"

namespace ft
{
	namespace
	{
		template <class T, class Compare>
		struct Node {
			Node(Compare comp, T pair, bool end = false) 
			: pair(pair), left(NULL), right(NULL), height(1), comp(comp), end(end) {}
			Node(const Node& other) 
			: pair(other.pair), left(NULL), right(NULL), height(1),
				comp(other.comp), end(false) {
				*this = other;
			}
			Node& operator=(const Node& other) {
				//this->setPair(other.pair);
				this->pair = other.pair;
				this->left = other.left;
				this->right = other.right;
				this->height = other.height;
				this->comp = other.comp;
				return *this;
			}
			~Node() {}
	
			T			pair;
			Node		*left;
			Node		*right;
			int			height;
		private:
			Compare		comp;
			const bool	end;
		};
	
		template <class T, class Compare>
		int height(Node<T, Compare> *node) {
		if (node == NULL)
			return 0;
		return node->height;
		}

		template <class T, class Compare>
		int getBalanceFactor(Node<T, Compare> *node) {
			if (node == NULL)
				return 0;
			return height(node->left) - height(node->right);
		}
	}

	template <class Key, class T, class Compare, class Alloc>
	class AVL
	{
	public:
		typedef				Key											key_type;
		typedef				T											mapped_type;
		typedef typename	ft::pair<key_type, mapped_type>		value_type;
		typedef 			Compare										key_compare;
		typedef				Node<value_type, key_compare>				node_type;
		typedef typename	Alloc::template rebind<node_type>::other	allocator_type;
		typedef				size_t										size_type;

		// Constructor & Destructor
		AVL(const key_compare& comp, const allocator_type& alloc)
		: root(NULL), endd(comp, value_type(), true), end_ptr(&endd),
			sizee(0), comp(comp), alloc(alloc) {}
		AVL(const AVL& other)
		: root(NULL), endd(comp, value_type(), true), end_ptr(&endd),
			sizee(0), comp(other.comp) {
			*this = other;
		}
		AVL& operator=(const AVL& other) {
			// Copying all nodes (by reallocation)
			if (other.root) {
				if (this->root)
					this->deleteRoot();
				this->root = this->createNode(other.root->pair);
				this->root = this->copyDescendants(this->root, other.root);
			}
			// Other attributes
			this->sizee = other.sizee;
			this->comp = other.comp;
			return *this;
		}
		~AVL() {
			this->deleteRoot();
		}

		// Methods
		void insert(value_type pair) {
			this->root = this->insertNode(this->root, pair);
		}

		void erase(key_type key) {
			this->root = this->deleteNode(this->root, key);
		}

		void print() {
			this->print(this->root, "", true);
			std::cout << std::endl;
		}

	private:
		node_type		*root;
		node_type		endd;
		const node_type	*end_ptr; // Only for const end(), is equal to &endd
		size_type		sizee;

		// Map traits
		key_compare		comp;
		allocator_type	alloc;

		// Allocation Manager
		void deleteRoot() {
			if (this->root)
				this->deleteNodeAndItsDescendants(this->root);
			this->sizee = 0;
		}
		node_type* createNode(const value_type& pair) {
			node_type *ret = this->alloc.allocate(1);
			this->alloc.construct(ret, node_type(this->comp, pair));
			return ret;
		}
		void deleteNode(node_type *node) {
			this->alloc.destroy(node);
			this->alloc.deallocate(node, 1);
		}
		void deleteNodeAndItsDescendants(node_type* node) {
			if (node->left)
				this->deleteNodeAndItsDescendants(node->left);
			if (node->right)
				this->deleteNodeAndItsDescendants(node->right);
			this->deleteNode(node);
		}

		// Utils
		node_type* copyDescendants(node_type* node, const node_type* other) {
			if (other->left) {
				node->left = this->createNode(other->left->pair);
				node->left = this->copyDescendants(node->left, other->left);
			}
			if (other->right) {
				node->right = this->createNode(other->right->pair);
				node->right = this->copyDescendants(node->right, other->right);
			}
		}
		void print(node_type *node, std::string indent, bool last) {
  			if (node != NULL) {
    			std::cout << indent;
    			if (last) {
					std::cout << "R----";
					indent += "   ";
				} else {
					std::cout << "L----";
					indent += "|  ";
				}
				std::cout << node->pair.first << std::endl;
				this->print(node->left, indent, false);
				this->print(node->right, indent, true);
			}
		}

		/// AVL BALANCE MANAGER ///
		// insert/erase + self-balancing
		node_type *insertNode(node_type *node, value_type pair) {
			// Insert
			if (node == NULL)
				return (this->createNode(pair));
			if (pair.first < node->pair.first)
				node->left = insertNode(node->left, pair);
			else if (pair.first > node->pair.first)
				node->right = insertNode(node->right, pair);
			else
				return node;

			// Update balance factors and balance the tree
			node->height = 1 + std::max(height(node->left),
										height(node->right));
			int balanceFactor = getBalanceFactor(node);
			if (balanceFactor > 1) {
				if (pair.first < node->left->pair.first)
					return rightRotate(node);
				else if (pair.first > node->left->pair.first) {
					node->left = leftRotate(node->left);
					return rightRotate(node);
				}
			}
			if (balanceFactor < -1) {
				if (pair.first > node->right->pair.first)
					return leftRotate(node);
				else if (pair.first < node->right->pair.first) {
					node->right = rightRotate(node->right);
					return leftRotate(node);
				}
			}
			return node;
		}
		node_type *deleteNode(node_type *root, key_type key) {
			// Delete
			if (root == NULL)
				return root;
			if (key < root->pair.first)
				root->left = deleteNode(root->left, key);
			else if (key > root->pair.first)
				root->right = deleteNode(root->right, key);
			else {
				if ((root->left == NULL) || (root->right == NULL)) {
					node_type *temp = root->left ? root->left : root->right;
					if (temp == NULL) {
						temp = root;
						root = NULL;
					} else
						*root = *temp;
					this->deleteNode(temp);
				} else {
					node_type *temp = root->right;
					while (temp->left)
						temp = temp->left;
					root->pair.first = temp->pair.first;
					root->right = deleteNode(root->right,
					temp->pair.first);
				}
			}
			if (root == NULL)
				return root;

			// Update balance factors and balance the tree
			root->height = 1 + std::max(height(root->left),
										height(root->right));
			int balanceFactor = getBalanceFactor(root);
			if (balanceFactor > 1) {
				if (getBalanceFactor(root->left) >= 0)
					return rightRotate(root);
				else {
					root->left = leftRotate(root->left);
					return rightRotate(root);
				}
			}
			if (balanceFactor < -1) {
				if (getBalanceFactor(root->right) <= 0)
					return leftRotate(root);
				else {
					root->right = rightRotate(root->right);
					return leftRotate(root);
				}
			}
			return root;
		}
		// Rotations
		node_type *rightRotate(node_type *y) {
			node_type *x = y->left;
			node_type *T2 = x->right;

			x->right = y;
			y->left = T2;
			y->height = std::max(height(y->left),
								height(y->right)) + 1;
			x->height = std::max(height(x->left),
								height(x->right)) + 1;
			return x;
		}
		node_type *leftRotate(node_type *x) {
			node_type *y = x->right;
			node_type *T2 = y->left;

			y->left = x;
			x->right = T2;
			x->height = std::max(height(x->left),
								height(x->right)) + 1;
			y->height = std::max(height(y->left),
								height(y->right)) + 1;
			return y;
		}
		/// /////////////////// ///
	};
}

#endif // AVL_HPP