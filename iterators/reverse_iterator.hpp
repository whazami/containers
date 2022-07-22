#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "../utils/iterator_traits.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
	public :
		typedef				Iterator											iterator_type;
		typedef typename	ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename	ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename	ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename	ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename	ft::iterator_traits<Iterator>::reference			reference;

		// Constructors
		reverse_iterator() : it() {}

		explicit reverse_iterator(iterator_type it) : it(it){}

		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it) : it(rev_it.base()) {}

		template<class U>
		reverse_iterator& operator=(const reverse_iterator<U>& other) {
			this->it = other.base();
			return *this;
		}

		iterator_type base() const {
			return this->it;
		}

		reference operator*() const {
			iterator_type tmp = this->it;
			return (*--tmp);
		}

		// Operators
		reverse_iterator operator+(difference_type n) const {
			reverse_iterator rev(this->base() - n);
			return rev;
		}

		reverse_iterator& operator++() {	// Pre-incrementation
			this->it--;
			return *this;
		}
		reverse_iterator operator++(int) {	// Post-incrementation
			reverse_iterator tmp(*this);
			this->operator++();
			return tmp;
		}

		reverse_iterator& operator+=(difference_type n) {
			this->it -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(this->base() + n);
		}

		reverse_iterator& operator--() {	// Pre-incrementation
			this->it++;
			return *this;
		}
		reverse_iterator operator--(int) {	// Post-incrementation
			reverse_iterator tmp(*this);
			this->operator--();
			return tmp;
		}

		reverse_iterator& operator-=(difference_type n) {
			this->it += n;
			return *this;
		}

		pointer operator->() const {
			return &(operator*());
		}

		reference operator[](difference_type n) const {
			reverse_iterator rev = *this + n;
			return *rev;
		}

	protected :
		iterator_type it;
	};

	// Relational Operators
	template <class Iterator1, class Iterator2> 
	bool operator==(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator<(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() > rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() >= rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator>(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template <class Iterator>
	ft::reverse_iterator<Iterator> operator+(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& rev_it) {
		return rev_it + n;
	}
	template <class Iterator1, class Iterator2>
	typename ft::reverse_iterator<Iterator1>::difference_type operator-(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return rhs.base() - lhs.base();
	}
}

#endif // REVERSE_ITERATOR_HPP
