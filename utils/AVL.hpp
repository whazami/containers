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
			Node(Compare comp, T pair, Node *endd) 
			: pair(pair), left(NULL), right(NULL), parent(NULL),
				height(1), comp(comp), endd(endd) {}
			Node(const Node& other) 
			: pair(other.pair), left(NULL), right(NULL), parent(NULL),
				height(1), comp(other.comp), endd(other.endd) {
				*this = other;
			}
			Node& operator=(const Node& other) {
				this->left = other.left;
				this->right = other.right;
				this->parent = NULL;
				this->height = other.height;
				this->comp = other.comp;
				this->endd = other.endd;
				return *this;
			}
			~Node() {}

			Node* next() {
				Node *p;
				if (this->right) {
					p = this->right;
					while (p->left)
						p = p->left;
				} else {
					p = this->parent;
					while (p && this->comp(p->pair.first, this->pair.first))
						p = p->parent;
				}
				if (!p)
					return endd;
				return p;
			}
			Node* prev() {
				Node *p;
				if (this->left) {
					p = this->left;
					while (p->right)
						p = p->right;
				} else {
					p = this->parent;
					while (p && this->comp(this->pair.first, p->pair.first))
						p = p->parent;
				}
				if (!p)
					return endd;
				return p;
			}
	
			T			pair;
			Node		*left;
			Node		*right;
			Node		*parent;
			int			height;
		private:
			Compare		comp;
			Node*		endd;
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

		template <class T, class Compare>
		bool operator<(const Node<T, Compare>& n1, const Node<T, Compare>& n2) {
			return n1.pair.first < n2.pair.first;
		}
	}

	template <class Key, class T, class Compare, class Alloc>
	class AVL
	{
	public:
		typedef				Key											key_type;
		typedef				T											mapped_type;
		typedef typename	ft::pair<const key_type, mapped_type>		value_type;
		typedef 			Compare										key_compare;
		typedef				Node<value_type, key_compare>				node_type;
		typedef typename	Alloc::template rebind<node_type>::other	allocator_type;
		typedef				size_t										size_type;

		// Constructor & Destructor
		AVL(const key_compare& comp, const allocator_type& alloc)
		: root(NULL), endd(comp, value_type(), NULL), end_ptr(&endd),
			sizee(0), comp(comp), alloc(alloc) {}
		AVL(const AVL& other)
		: root(NULL), endd(other.comp, value_type(), NULL), end_ptr(&endd),
			sizee(0), comp(other.comp) {
			*this = other;
		}
		AVL& operator=(const AVL& other) {
			this->endd.right = NULL;
			this->endd.left = NULL;
			// Copying all nodes (by reallocation)
			if (other.root) {
				if (this->root)
					this->deleteRoot();
				this->root = this->createNode(other.root->pair);
				this->root = this->copyDescendants(this->root, other.root);
				node_type* p = this->root;
				while (p->right)
					p = p->right;
				this->endd.right = p;
				this->endd.left = p;
			}
			// Other attributes
			this->sizee = other.sizee;
			this->comp = other.comp;
			this->end_ptr = &this->endd;
			return *this;
		}
		~AVL() {
			this->deleteRoot();
		}

		// Methods
		bool insert(value_type pair) {
			return this->insert(pair, &this->root);
		}
		bool insert(value_type pair, node_type **node) {
			bool exists = (this->find(pair.first) != NULL);
			*node = this->insertNode(*node, pair);
			if (!exists) {
				if (this->sizee == 0) {
					this->endd.right = *node;
					this->endd.left = *node;
				} else if (this->endd.right->right) {
					this->endd.left = this->endd.right->right;
					this->endd.right = this->endd.right->right;
				}
				this->sizee++;
			}
			return !exists;
		}

		bool erase(key_type key) {
			if (!this->find(key))
				return false;
			if (!this->comp(key, this->endd.right->pair.first)
				&& !this->comp(this->endd.right->pair.first, key)) {
				this->endd.left = this->endd.right->prev();
				this->endd.right = this->endd.right->prev();
			}
			this->root = this->deleteNode(this->root, key);
			this->sizee--;
			return true;
		}

		node_type *find(key_type key) const {
			node_type *p = this->root;
			while (p && (this->comp(key, p->pair.first)
							|| this->comp(p->pair.first, key)))
				p = this->comp(key, p->pair.first) ? p->left : p->right;
			return p;
		}

		node_type *begin() const {
			if (!this->root)
				return this->end_ptr;
			node_type *p = this->root;
			while (p->left)
				p = p->left;
			return p;
		}

		node_type *end() const {
			return this->end_ptr;
		}

		size_type size() const {
			return this->sizee;
		}

		void clear() {
			this->deleteRoot();
		}

		void swap(AVL& other) {
			std::swap(this->root, other.root);
			std::swap(this->end_ptr, other.end_ptr);
			std::swap(this->sizee, other.sizee);
			std::swap(this->comp, other.comp);
		}

		key_compare get_comp() const {
			return this->comp;
		}
		allocator_type get_alloc() const {
			return this->alloc;
		}

		void print() {
			this->print("", this->root, true);
			std::cout << std::endl;
		}

		node_type *getRoot() {
			return this->root;
		}

		template <class Key2, class T2, class Compare2, class Alloc2>
		friend bool operator==(const AVL<Key2, T2, Compare2, Alloc2>& lhs, const AVL<Key2, T2, Compare2, Alloc2>& rhs);
		template <class Key2, class T2, class Compare2, class Alloc2>
		friend bool operator!=(const AVL<Key2, T2, Compare2, Alloc2>& lhs, const AVL<Key2, T2, Compare2, Alloc2>& rhs);
		template <class Key2, class T2, class Compare2, class Alloc2>
		friend bool operator<(const AVL<Key2, T2, Compare2, Alloc2>& lhs, const AVL<Key2, T2, Compare2, Alloc2>& rhs);
		template <class Key2, class T2, class Compare2, class Alloc2>
		friend bool operator<=(const AVL<Key2, T2, Compare2, Alloc2>& lhs, const AVL<Key2, T2, Compare2, Alloc2>& rhs);
		template <class Key2, class T2, class Compare2, class Alloc2>
		friend bool operator>(const AVL<Key2, T2, Compare2, Alloc2>& lhs, const AVL<Key2, T2, Compare2, Alloc2>& rhs);
		template <class Key2, class T2, class Compare2, class Alloc2>
		friend bool operator>=(const AVL<Key2, T2, Compare2, Alloc2>& lhs, const AVL<Key2, T2, Compare2, Alloc2>& rhs);

	private:
		node_type		*root;
		node_type		endd;
		node_type		*end_ptr; // Only for const end(), is equal to &endd
		size_type		sizee;

		// Map traits
		key_compare		comp;
		allocator_type	alloc;

		// Allocation Manager
		void deleteRoot() {
			if (this->root)
				this->deleteNodeAndItsDescendants(this->root);
			this->root = NULL;
			this->sizee = 0;
		}
		node_type* createNode(const value_type& pair) {
			node_type *ret = this->alloc.allocate(1);
			this->alloc.construct(ret, node_type(this->comp, pair, &this->endd));
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
				node->left->parent = node;
				node->left = this->copyDescendants(node->left, other->left);
			}
			if (other->right) {
				node->right = this->createNode(other->right->pair);
				node->right->parent = node;
				node->right = this->copyDescendants(node->right, other->right);
			}
			return node;
		}
		node_type *setPair(node_type *node, value_type pair) {
			const node_type* node_addr = node;
			node_type tmp = *node;
			tmp.parent = node->parent;
			this->deleteNode(node);
			node_type *ret = this->createNode(pair);
			*ret = tmp;
			ret->parent = tmp.parent;
			if (ret->left)
				ret->left->parent = ret;
			if (ret->right)
				ret->right->parent = ret;
			if (ret->parent) {
				bool isLeftChild = (ret->parent->left == node_addr);
				if (isLeftChild)
					ret->parent->left = ret;
				else
					ret->parent->right = ret;
			}
			if (!this->comp(this->endd.right->pair.first, ret->pair.first)
				&& !this->comp(ret->pair.first, this->endd.right->pair.first)) {
				this->endd.left = ret;
				this->endd.right = ret;
			}
			return ret;
		}

		void print(const std::string& prefix, const node_type* node, bool isLeft) {
			if (node) {
				std::cout << prefix;
				std::cout << (!isLeft ? "├──" : "└──");
				std::cout << node->pair.first << std::endl;
				this->print(prefix + (!isLeft ? "│   " : "    "), node->right, false);
				this->print(prefix + (!isLeft ? "│   " : "    "), node->left, true);
			}
		}

		/// AVL BALANCE MANAGER ///
		// insert/erase + self-balancing
		node_type *insertNode(node_type *node, value_type pair) {
			// Insert
			if (node == NULL)
				return (this->createNode(pair));
			if (this->comp(pair.first, node->pair.first)) {
				node->left = insertNode(node->left, pair);
				node->left->parent = node;
			}
			else if (this->comp(node->pair.first, pair.first)) {
				node->right = insertNode(node->right, pair);
				node->right->parent = node;
			}
			else {
				node->pair.second = pair.second;
				return node;
			}

			// Update balance factors and balance the tree
			node->height = 1 + std::max(height(node->left),
										height(node->right));
			int balanceFactor = getBalanceFactor(node);
			if (balanceFactor > 1) {
				if (this->comp(pair.first, node->left->pair.first))
					return rightRotate(node);
				else if (this->comp(node->left->pair.first, pair.first)) {
					node->left = leftRotate(node->left);
					return rightRotate(node);
				}
			}
			if (balanceFactor < -1) {
				if (this->comp(node->right->pair.first, pair.first))
					return leftRotate(node);
				else if (this->comp(pair.first, node->right->pair.first)) {
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
			if (this->comp(key, root->pair.first))
				root->left = deleteNode(root->left, key);
			else if (this->comp(root->pair.first, key))
				root->right = deleteNode(root->right, key);
			else {
				if ((root->left == NULL) || (root->right == NULL)) {
					node_type *temp = root->left ? root->left : root->right;
					if (temp == NULL) {
						temp = root;
						root = NULL;
					} else {
						node_type* save_parent = temp->parent ? temp->parent->parent : NULL;
						*root = *temp;
						root = this->setPair(root, temp->pair);
						root->parent = save_parent;
					}
					this->deleteNode(temp);
				} else {
					node_type *temp = root->right;
					while (temp->left)
						temp = temp->left;
					root = this->setPair(root, temp->pair);
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
			x->parent = y->parent;
			y->parent = x;
			if (y->left)
				y->left->parent = y;
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
			y->parent = x->parent;
			x->parent = y;
			if (x->right)
				x->right->parent = x;
			return y;
		}
		/// /////////////////// ///
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const AVL<Key, T, Compare, Alloc>& lhs,
					const AVL<Key, T, Compare, Alloc>& rhs) {
		if (lhs.sizee != rhs.sizee)
			return false;
		for (typename AVL<Key, T, Compare, Alloc>::node_type *n1 = lhs.begin(), *n2 = rhs.begin()
				; n1 != lhs.end(); n1 = n1->next(), n2 = n2->next())
			if (n1->pair != n2->pair)
				return false;
		return true;
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const AVL<Key, T, Compare, Alloc>& lhs,
					const AVL<Key, T, Compare, Alloc>& rhs) {
		return !(lhs == rhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const AVL<Key, T, Compare, Alloc>& lhs,
					const AVL<Key, T, Compare, Alloc>& rhs) {
		typename AVL<Key, T, Compare, Alloc>::node_type *first1 = lhs.begin();
		typename AVL<Key, T, Compare, Alloc>::node_type *last1 = lhs.end();
		typename AVL<Key, T, Compare, Alloc>::node_type *first2 = rhs.begin();
		typename AVL<Key, T, Compare, Alloc>::node_type *last2 = rhs.end();

		while (first1 != last1) {
			if (first2 == last2 || operator<(first2->pair, first1->pair))
				return false;
			else if (operator<(first1->pair, first2->pair))
				return true;
			first1 = first1->next();
			first2 = first2->next();
		}
		return (first2 != last2);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const AVL<Key, T, Compare, Alloc>& lhs,
					const AVL<Key, T, Compare, Alloc>& rhs) {
		return !(rhs < lhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const AVL<Key, T, Compare, Alloc>& lhs,
					const AVL<Key, T, Compare, Alloc>& rhs) {
		return rhs < lhs;
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const AVL<Key, T, Compare, Alloc>& lhs,
					const AVL<Key, T, Compare, Alloc>& rhs) {
		return !(lhs < rhs);
	}
}

#endif // AVL_HPP
