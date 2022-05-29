#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>
#include "pair.hpp"

namespace ft
{
	namespace
	{
		template <class Key, class T, class Compare, class Alloc>
		class Node
		{
		public:
			typedef				Key											key_type;
			typedef				T											mapped_type;
			typedef				Compare										key_compare;
			typedef typename	ft::pair<key_type, mapped_type>				value_type;
			typedef typename	Alloc::template rebind<Node<key_type,
								mapped_type, key_compare, Alloc> >::other	allocator_type;
			typedef typename	ft::pair<key_compare, allocator_type>		map_traits_type;

			// Constructor & Destructors
			Node(const map_traits_type& map_traits, const value_type& pair)
			: left(NULL), right(NULL), parent(NULL), pair(pair),
			  compare(map_traits.first), alloc(map_traits.second) {}

			Node(Node *parent, const map_traits_type& map_traits, const value_type& pair)
			: left(NULL), right(NULL), parent(parent), pair(pair),
			  compare(map_traits.first), alloc(map_traits.second) {}

			Node(const Node &other)
			: left(other.left), right(other.right), parent(other.parent),
			  pair(other.pair), compare(other.compare), alloc(other.alloc) {}

			Node& operator=(const Node& other) {
				this->left = other.left;
				this->right = other.right;
				this->parent = other.parent;
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

			mapped_type operator*() const {
				return this->pair.second;
			}

			// Methods
			Node* next(const key_type& key) const {
				return this->compare(key, this->pair.first) ? this->left : this->right;
			}

			void add(const value_type& pair) {
				if (this->pair.first == pair.first) {
					this->pair.second = pair.second;
					return;
				}
				bool left = this->compare(pair.first, this->pair.first);
				Node *child = left ? this->left : this->right;
				if (!child)
					this->createChild(pair, left);
				else
					child->add(pair);
			}

			void erase() {
				Node *p = this->left ? this->left : this->right;
				if (this->relinkToChild(p, NULL))
					return ;
				if (this->relinkToChild(p, &this->right))
					return ;
				while (p->right)
					p = p->right;
				if (this->relinkToChild(p, &this->left, !this->right))
					return ;
				this->pair = p->pair;
				this->changeParentPOV(p, p->left ? &p->left : NULL);
				this->deallocate(p);
			}

		private:
			// Links to the tree
			Node			*left;
			Node			*right;
			Node			*parent;

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

			bool relinkToChild(Node *p, Node **child, bool additionalCond = true) {
				if (p == (child ? *child : NULL) && additionalCond) {
					this->changeParentPOV(this, child);
					this->deallocate(this);
					return true;
				}
				return false;
			}
		};
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
		typedef 			const p_node_type								node_type;
		typedef typename	Alloc::template rebind<p_node_type>::other		allocator_type;
		typedef typename	ft::pair<key_compare, allocator_type>			map_traits_type;
		typedef 			size_t											size_type;

		// Constructors & Destructors
		BinaryTree(const typename ft::pair<key_compare, Alloc>& map_traits)
		: root(NULL), size(0), map_traits(map_traits) {}
		BinaryTree(const BinaryTree& other)
		: root(NULL), size(0), map_traits(other.map_traits) {
			*this = other;
		}
		BinaryTree& operator=(const BinaryTree& other) {
			this->root = other.root;
			this->size = other.size;
			this->map_traits.first = other.map_traits.first;
		}
		~BinaryTree() {
			this->deleteRoot();
		}

		// Methods
		void insert(const value_type& pair) {
			if (!this->root)
				this->createRoot(pair);
			else
				this->root->add(pair);
			this->size++;
		}

		bool erase(const key_type& key) {
			p_node_type *p = this->find(key);
			if (!p)
				return false;
			p->erase();
			this->size--;
			return true;
		}

		p_node_type *find(const key_type& key) {
			p_node_type *ret = this->root;
			while (ret && *ret != key)
				ret = ret->next(key);
			return ret;
		}

	private:
		p_node_type*	root;
		size_type		size;
		map_traits_type	map_traits;

		// Allocation Manager
		void createRoot(const value_type& pair) {
			this->root = this->map_traits.second.allocate(1);
			this->map_traits.second.construct(this->root, p_node_type(this->map_traits, pair));
		}
		void deleteRoot() {
			if (this->root)
				this->map_traits.second.destroy(this->root);
			this->map_traits.second.deallocate(this->root, 1);
		}
	};
}
#endif // BINARYTREE_HPP
