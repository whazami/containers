#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <iostream>
# include <iterator>

namespace ft
{
	template <class T>
	class vector_iterator : public std::iterator<std::random_access_iterator_tag, T>
	{
	private:
		typedef typename std::iterator<std::random_access_iterator_tag, T> iterator;
	public:
		typedef typename iterator::value_type			value_type;
		typedef typename iterator::difference_type		difference_type;
		typedef typename iterator::pointer				pointer;
		typedef typename iterator::reference			reference;
		typedef typename iterator::iterator_category	iterator_category;
		
		// Canonical form
		vector_iterator() : p(NULL) {}
		vector_iterator(pointer p) : p(p) {}
		vector_iterator(const vector_iterator &it) {
			*this = it;
		}
		vector_iterator	&operator=(const vector_iterator& it) {
			this->p = it.p;
			return *this;
		}
		template <typename U>
		operator vector_iterator<const U>() const {
			vector_iterator<const U> ret((const U*)this->p);
			return ret;
		}

		/// OPERATORS
		// Equality Comparisons
		bool operator==(const vector_iterator& rhs) const {
			if (this->p == rhs.p)
				return true;
			return false;
		}
		bool operator!=(const vector_iterator& rhs) const {
			return !(*this == rhs);
		}
		template <typename U, typename V>
		friend bool operator==(const vector_iterator<U>& lhs, const vector_iterator<V>& rhs);
		template <typename U, typename V>
		friend bool operator!=(const vector_iterator<U>& lhs, const vector_iterator<V>& rhs);

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
		vector_iterator &operator++() { // Pre-incrementation
			this->p++;
			return *this;
		}
		vector_iterator	operator++(int) { // Post-incrementation
			vector_iterator tmp(*this);
			this->operator++();
			return tmp;
		}
		vector_iterator &operator--() { // Pre-decrementation
			this->p--;
			return *this;
		}
		vector_iterator	operator--(int) { // Post-decrementation
			vector_iterator tmp(*this);
			this->operator--();
			return tmp;
		}

		// Arithmetic operations
		vector_iterator operator+(int n) const {
			return this->p + n;
		}
		vector_iterator operator-(int n) const {
			return this->p - n;
		}
		difference_type operator-(const vector_iterator& rhs) const {
			return this->p - rhs.p;
		}
		template <typename U, typename V>
		friend typename vector_iterator<U>::difference_type operator-(
					const vector_iterator<U>& lhs, const vector_iterator<V>& rhs);

		// Inequality Comparisons
		bool operator<(const vector_iterator& rhs) const {
			if (this->p < rhs.p)
				return true;
			return false;
		}
		bool operator>(const vector_iterator& rhs) const {
			return (rhs < *this);
		}
		bool operator<=(const vector_iterator& rhs) const {
			return (*this < rhs || *this == rhs);
		}
		bool operator>=(const vector_iterator& rhs) const {
			return (rhs < *this || *this == rhs);
		}
		template <typename U, typename V>
		friend bool operator<(const vector_iterator<U>& lhs, const vector_iterator<V>& rhs);
		template <typename U, typename V>
		friend bool operator>(const vector_iterator<U>& lhs, const vector_iterator<V>& rhs);
		template <typename U, typename V>
		friend bool operator<=(const vector_iterator<U>& lhs, const vector_iterator<V>& rhs);
		template <typename U, typename V>
		friend bool operator>=(const vector_iterator<U>& lhs, const vector_iterator<V>& rhs);

		// Increment & Decrement assigment
		vector_iterator &operator+=(const int n) {
			this->p += n;
			return *this;
		}
		vector_iterator &operator-=(const int n) {
			this->p -= n;
			return *this;
		}

		// Offset dereference
		value_type operator[](int i) const {
			vector_iterator tmp = *this + i;
			return *tmp;
		}
		value_type &operator[](int i) {
			vector_iterator tmp = *this + i;
			return *tmp;
		}

	private:
		pointer	p;	
	};
	
	template <class T>
	vector_iterator<T> operator+(int n, vector_iterator<T> vit) {
		return vit + n;
	}

	template <typename T, typename U>
	bool operator==(const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
		if (lhs.p == rhs.p)
			return true;
		return false;
	}
	template <typename T, typename U>
	bool operator!=(const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
		return !(lhs == rhs);
	}
	
	template <typename T, typename U>
	typename vector_iterator<T>::difference_type operator-(
				const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
		return lhs.p - rhs.p;
	}

	template <typename T, typename U>
	bool operator<(const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
		if (lhs.p < rhs.p)
			return true;
		return false;
	}
	template <typename T, typename U>
	bool operator>(const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
		return (rhs < lhs);
	}
	template <typename T, typename U>
	bool operator<=(const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
		return (lhs < rhs || lhs == rhs);
	}
	template <typename T, typename U>
	bool operator>=(const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
		return (rhs < lhs || lhs == rhs);
	}
}

#endif // ITERATOR_HPP
