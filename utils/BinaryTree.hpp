#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>
#include "pair.hpp"

namespace ft
{
	namespace
	{
		/* --- Some forward declarations for non-member method 'isLeaf' --- */
		template <class Key, class T, class Compare, class Alloc>
		class Node;

		template <class Key, class T, class Compare, class Alloc>
		bool isLeaf(Node<Key, T, Compare, Alloc> *node);
		/* --- -------------------------------------------------------- --- */

		template <class Key, class T, class Compare, class Alloc>
		class Node
		{
		public:
			typedef				Key											key_type;
			typedef				T											mapped_type;
			typedef				Compare										key_compare;
			typedef typename	ft::pair<const key_type, mapped_type>		value_type;
			typedef typename	Alloc::template rebind<Node<key_type,
								mapped_type, key_compare, Alloc> >::other	allocator_type;
			typedef typename	ft::pair<key_compare, allocator_type>		map_traits_type;

			// Constructor & Destructors
			Node(const map_traits_type& map_traits, const value_type& pair)
			: left(NULL), right(NULL), parent(NULL), end(false), pair(pair),
			  compare(map_traits.first), alloc(map_traits.second) {}

			Node(Node *parent, const map_traits_type& map_traits, const value_type& pair)
			: left(NULL), right(NULL), parent(parent), end(false), pair(pair),
			  compare(map_traits.first), alloc(map_traits.second) {}

			Node() : left(NULL), right(NULL), parent(NULL), end(true),
					 pair(value_type()), compare(Compare()), alloc(allocator_type())
			{}

			Node(const Node &other) : left(other.left), right(other.right),
				parent(other.parent), end(other.end), pair(other.pair),
				compare(other.compare), alloc(other.alloc) {}

			Node& operator=(const Node& other) {
				this->left = other.left;
				this->right = other.right;
				this->parent = other.parent;
				this->end = other.end;
				this->pair = other.pair;
				this->compare = other.compare;
				return *this;
			}

			~Node() {
				this->deallocate(this->left);
				this->deallocate(this->right);
			}

			// Operators
			bool operator==(const Node& other) const { return this->pair == other.pair; }
			bool operator==(const value_type& pair) const { return this->pair == pair; }
			bool operator==(const key_type& key) const { return this->pair.first == key; }
			bool operator!=(const Node& other) const { return !(*this == other); }
			bool operator!=(const value_type& pair) const { return  !(*this == pair); }
			bool operator!=(const key_type& key) const { return !(*this == key); }

			value_type operator*() const {
				return this->pair;
			}
			value_type *operator->() {
				return &this->pair;
			}
			value_type &operator*() {		// lvalue
				return this->pair;
			}

			// Methods
			Node* next(const key_type& key) const {
				return this->compare(key, this->pair.first) ? this->left : this->right;
			}
			Node* next() const {
				Node *p;
				if (this->right) {
					p = this->right;
					if (!p->end)
						while (!isLeaf(p->left))
							p = p->left;
				} else {
					p = this->parent;
					while (p && this->parent->pair.first < this->pair.first)
						p = p->parent;
				}
				return p;
			}

			Node* add(const value_type& pair) {
				if (this->pair.first == pair.first) {
					this->pair.second = pair.second;
					return this;
				}
				bool left = this->compare(pair.first, this->pair.first);
				Node *child = left ? this->left : this->right;
				if (!child || (child && child->end)) {
					this->createChild(pair, left);
					return left ? this->left : this->right;
				}
				else
					return child->add(pair);
			}

			Node* erase() {
				Node *p = this->left ? this->left : this->right, *ret;
				if (this->relinkToChild(p, NULL))								// No children
					return NULL;
				if ((ret = this->relinkToChild(p, &this->right)))				// Only right
					return ret;
				while (p->right)
					p = p->right;
				if ((ret = this->relinkToChild(p, &this->left, !this->right)))	// Only left
					return ret;
				Node *newRoot = p;
				while (newRoot->parent)
					newRoot = newRoot->parent;
				this->pair = p->pair;											// Both
				this->changeParentPOV(p, p->left ? &p->left : NULL);
				this->deallocate(p);
				return newRoot;
			}

			Node *begin() {
				Node* p = this;
				while (p->parent)
					p = p->parent;
				while (!isLeaf(p->left))
					p = p->left;
				return p;
			}

			// node -> end
			// this -> p
			void loop(Node *node, bool checkOrder) {
				if (!checkOrder || node->left->pair.first < this->pair.first) {
					this->right = node;
					node->left = this;
				}
				if (!checkOrder || node->right->pair.first > this->pair.first) {
					this->left = node;
					node->right = this;
				}
			}

			// Specific function for end node
			void unlink() {
				if (this->left)
					this->left->right = NULL;
				if (this->right)
					this->right->left = NULL;
				this->right = NULL;
				this->left = NULL;
			}

			friend bool isLeaf<Key, T, Compare, Alloc>(Node *node);

		private:
			// Links to the tree
			Node			*left;
			Node			*right;
			Node			*parent;
			bool			end;

			// Data
			value_type		pair;

			// Map variables
			key_compare		compare;
			allocator_type	alloc;

			// Utils
			void createChild(const value_type& pair, bool left) {
				Node **child = left ? &this->left : &this->right;
				*child = this->alloc.allocate(1);
				this->alloc.construct(*child,
					Node(this, ft::make_pair(this->compare, this->alloc), pair));
			}

			void deallocate(Node *p) {
				if (p)
					this->alloc.destroy(p);
				this->alloc.deallocate(p, 1);
			}

			void changeParentPOV(Node *p, Node **newPOV) {
				if (!p->parent)
					return ;
				bool pIsLeftChild = (p == p->parent->left);
				Node **pFromParentPOV = pIsLeftChild ? &p->parent->left : &p->parent->right;
				*pFromParentPOV = newPOV ? *newPOV : NULL;
				if (newPOV)
					(*newPOV)->parent = p->parent;
				p->left = NULL;
				p->right = NULL;
			}

			Node* relinkToChild(Node *p, Node **child, bool additionalCond = true) {
				if (p == (child ? *child : NULL) && additionalCond) {
					if (p && !p->parent->parent) { // if we're erasing the root and it has one and only one child
						*child = NULL;
						this->deallocate(p->parent);
						p->parent = NULL;
					} else {
						this->changeParentPOV(this, child);
						this->deallocate(this);
					}
					if (!p)
						return this;
					while (p->parent)
						p = p->parent;
					return p;
				}
				return NULL;
			}
		};

		template <class Key, class T, class Compare, class Alloc>
		bool isLeaf(Node<Key, T, Compare, Alloc> *node) {
			return !node || node->end;
		}
	}

	template <class Key, class T, class Compare, class Alloc>
	class BinaryTree
	{
	public:
		typedef 			Key												key_type;
		typedef 			T												mapped_type;
		typedef typename	ft::pair<const key_type, mapped_type>			value_type;
		typedef				Compare											key_compare;
	private:
		typedef 			Node<key_type, mapped_type, key_compare, Alloc>	p_node_type;
	public:
		typedef 			p_node_type								node_type;
		typedef typename	Alloc::template rebind<p_node_type>::other		allocator_type;
		typedef typename	ft::pair<key_compare, allocator_type>			map_traits_type;
		typedef 			size_t											size_type;

		// Constructors & Destructors
		BinaryTree(const typename ft::pair<key_compare, Alloc>& map_traits)
		: root(NULL), sizee(0), map_traits(map_traits) {}
		BinaryTree(const BinaryTree& other)
		: root(NULL), sizee(0), map_traits(other.map_traits) {
			*this = other;
		}
		BinaryTree& operator=(const BinaryTree& other) {
			this->root = other.root;
			this->sizee = other.sizee;
			this->map_traits.first = other.map_traits.first;
			return *this;
		}
		~BinaryTree() {
			this->deleteRoot();
		}

		// Methods
		p_node_type* insert(const value_type& pair) {
			this->sizee++;
			if (!this->root) {
				this->createRoot(pair);
				return this->root;
			}
			else {
				p_node_type *p = this->root->add(pair);
				p->loop(&this->endd, true);
				return p;
			}
		}

		bool erase(const key_type& key) {
			p_node_type *p = this->find(key);
			if (!p)
				return false;
			p_node_type *newRoot = p->erase();
			this->root = newRoot ? newRoot : this->root;
			if (--this->sizee == 0)
				this->root = NULL;
			return true;
		}

		p_node_type *find(const key_type& key) const {
			p_node_type *ret = this->root;
			while (!isLeaf(ret) && *ret != key)
				ret = ret->next(key);
			return isLeaf(ret) ? NULL : ret;
		}

		p_node_type *begin() const {
			if (!this->root)
				return NULL;
			return this->root->begin();
		}

		p_node_type *end() {
			p_node_type *ret = &this->endd;
			return ret;
		}

		size_type size() const {
			return this->sizee;
		}

	private:
		p_node_type*	root;
		p_node_type		endd;
		size_type		sizee;
		map_traits_type	map_traits;

		// Allocation Manager
		void createRoot(const value_type& pair) {
			this->root = this->map_traits.second.allocate(1);
			this->map_traits.second.construct(this->root, p_node_type(this->map_traits, pair));
			this->root->loop(&this->endd, false);
		}
		void deleteRoot() {
			this->endd.unlink();
			if (this->root)
				this->map_traits.second.destroy(this->root);
			this->map_traits.second.deallocate(this->root, 1);
		}
	};
}
#endif // BINARYTREE_HPP
