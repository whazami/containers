#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>
# include <iterator>

namespace ft
{
	template <class T>
	class map_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
	private:
		typedef typename std::iterator<std::bidirectional_iterator_tag, T> iterator;
	public:
		typedef typename iterator::value_type			value_type;
		typedef typename iterator::difference_type		difference_type;
		typedef typename iterator::pointer				pointer;
		typedef typename iterator::reference			reference;
		typedef typename iterator::iterator_category	iterator_category;
		
		// Canonical form
		map_iterator() : p(NULL) {}
		map_iterator(pointer p) : p(p) {}
		map_iterator(const map_iterator &it) {
			*this = it;
		}
		map_iterator	&operator=(const map_iterator& it) {
			this->p = it.p;
			return *this;
		}
		template <typename U>
		operator map_iterator<const U>() const {
			map_iterator<const U> ret((const U*)this->p);
			return ret;
		}

		/// OPERATORS
		// Equality Comparisons
		bool operator==(const map_iterator& rhs) const {
			if (this->p == rhs.p)
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
			return *this->p;
		}
		value_type *operator->() {
			return this->p;
		}
		value_type &operator*() { // Dereferencing as an lvalue
			return *this->p;
		}

		// Increment & Decrement
		map_iterator &operator++() { // Pre-incrementation
			this->p++;
			return *this;
		}
		map_iterator	operator++(int) { // Post-incrementation
			map_iterator tmp(*this);
			this->operator++();
			return tmp;
		}
		map_iterator &operator--() { // Pre-decrementation
			this->p--;
			return *this;
		}
		map_iterator	operator--(int) { // Post-decrementation
			map_iterator tmp(*this);
			this->operator--();
			return tmp;
		}

	private:
		pointer	p;	
	};

	template <typename T, typename U>
	bool operator==(const map_iterator<T>& lhs, const map_iterator<U>& rhs) {
		if (lhs.p == rhs.p)
			return true;
		return false;
	}
	template <typename T, typename U>
	bool operator!=(const map_iterator<T>& lhs, const map_iterator<U>& rhs) {
		return !(lhs == rhs);
	}
}

#endif // MAP_ITERATOR_HPP
