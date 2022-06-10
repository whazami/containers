#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>
# include <iterator>
# include "../utils/BinaryTree.hpp"

namespace ft
{
	template <class T, typename Node>
	class map_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
	private:
		typedef typename std::iterator<std::bidirectional_iterator_tag, T>	iterator;
		typedef Node*														node_ptr;
	public:
		typedef typename iterator::value_type			value_type;
		typedef typename iterator::difference_type		difference_type;
		typedef typename iterator::pointer				pointer;
		typedef typename iterator::reference			reference;
		typedef typename iterator::iterator_category	iterator_category;
		
		// Canonical form
		map_iterator() : node(NULL) {}
		map_iterator(node_ptr node) : node(node) {}
		map_iterator(const map_iterator &it) {
			*this = it;
		}
		map_iterator	&operator=(const map_iterator& it) {
			this->node = it.node;
			return *this;
		}
		template <typename U, typename Node2>
		operator map_iterator<const U, const Node2>() const {
			map_iterator<const U, const Node2> ret(this->node);
			return ret;
		}
		template <typename U>
		operator map_iterator<const U, Node>() const {
			map_iterator<const U, Node> ret(this->node);
			return ret;
		}

		/// OPERATORS
		// Equality Comparisons
		bool operator==(const map_iterator& rhs) const {
			if (this->node == rhs.node)
				return true;
			return false;
		}
		bool operator!=(const map_iterator& rhs) const {
			return !(*this == rhs);
		}
		template <class U, typename Node2, class V, typename Node3>
		friend bool operator==(const map_iterator<U, Node2>& lhs,
								const map_iterator<V, Node3>& rhs);
		template <class U, typename Node2, class V, typename Node3>
		friend bool operator!=(const map_iterator<U, Node2>& lhs,
								const map_iterator<V, Node3>& rhs);

		// Dereferencing
		value_type operator*() const {
			return **this->node;
		}
		value_type *operator->() {
			return &(**this->node);
		}
		value_type &operator*() { // Dereferencing as an lvalue
			return **this->node;
		}

		// Increment & Decrement
		map_iterator &operator++() { // Pre-incrementation
			this->node = this->node->next();
			return *this;
		}
		map_iterator	operator++(int) { // Post-incrementation
			map_iterator tmp(*this);
			this->operator++();
			return tmp;
		}
		map_iterator &operator--() { // Pre-decrementation
			// a faire
			return *this;
		}
		map_iterator	operator--(int) { // Post-decrementation
			map_iterator tmp(*this);
			this->operator--();
			return tmp;
		}

	private:
		node_ptr	node;
	};

	template <class U, typename Node2, class V, typename Node3>
	bool operator==(const map_iterator<U, Node2>& lhs,
					const map_iterator<V, Node3>& rhs) {
		if (lhs.node == rhs.node)
			return true;
		return false;
	}
	template <class U, typename Node2, class V, typename Node3>
	bool operator!=(const map_iterator<U, Node2>& lhs,
					const map_iterator<V, Node3>& rhs) {
		return !(lhs == rhs);
	}
}

#endif // MAP_ITERATOR_HPP
