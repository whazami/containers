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
		map_iterator(const map_iterator &it) {
			*this = it;
		}
		map_iterator	&operator=(const map_iterator& it) {
			this->node = it.node;
			return *this;
		}
		/*template <typename U>
		operator map_iterator<const U>() const {
			map_iterator<const U> ret((map_iterator<const U>)*this); // a revoir
			return ret;
		}*/

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
		template <typename U, typename V>
		friend bool operator==(const map_iterator<U>& lhs, const map_iterator<V>& rhs);
		template <typename U, typename V>
		friend bool operator!=(const map_iterator<U>& lhs, const map_iterator<V>& rhs);

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
			map_iterator end(this->node->end());
			if (*this == end)
				*this = 
			this->node = this->node->next();
			if (!this->node) {
				*this = end;
			}
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

		map_iterator(const node_ptr& node) : node(node) {}
	};

	template <typename T, typename U>
	bool operator==(const map_iterator<T>& lhs, const map_iterator<U>& rhs) {
		if (lhs.node == rhs.node)
			return true;
		return false;
	}
	template <typename T, typename U>
	bool operator!=(const map_iterator<T>& lhs, const map_iterator<U>& rhs) {
		return !(lhs == rhs);
	}
}

#endif // MAP_ITERATOR_HPP
