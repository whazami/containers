/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:38:23 by whazami           #+#    #+#             */
/*   Updated: 2022/05/24 20:01:06 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <iostream>

namespace ft
{
	template <	class T,											// iterator::value_type
				class Category = std::random_access_iterator_tag,	// iterator::iterator_category
				class Distance = std::ptrdiff_t,					// iterator::difference_type
				class Pointer = T*,									// iterator::pointer
				class Reference = T&>								// iterator::reference
	class vector_iterator
	{
	public:
		typedef T			value_type;			// Type of the elements pointed by the iterator
		typedef Distance	difference_type;	// Type to represent the difference between two iterators
		typedef Pointer		pointer;			// Type to represent a pointer to an element pointed by the iterator
		typedef Reference	reference;			// Type to represent a reference to an element pointed by the iterator
		typedef Category	iterator_category;	// Category to which the iterator belongs to.
		
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

		/// OPERATORS
		// Equality Comparisons
		bool operator==(vector_iterator rhs) const {
			if (this->p == rhs.p)
				return true;
			return false;
		}
		bool operator!=(vector_iterator rhs) const {
			return !(*this == rhs);
		}

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
		difference_type	operator-(vector_iterator rhs) const {
			return this->p - rhs.p;
		}

		// Inequality Comparisons
		bool operator<(vector_iterator rhs) const {
			if (this->p < rhs.p)
				return true;
			return false;
		}
		bool operator>(vector_iterator lhs) const {
			return (lhs < *this);
		}
		bool operator<=(vector_iterator lhs) const {
			return (*this < lhs || *this == lhs);
		}
		bool operator>=(vector_iterator lhs) const {
			return (lhs < *this || *this == lhs);
		}

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
	
	template <class T, class Category, class Distance, class Pointer, class Reference>
	vector_iterator<T, Category, Distance, Pointer, Reference>
	operator+(int n, vector_iterator<T, Category, Distance, Pointer, Reference> vit) {
		return vit + n;
	}
}

#endif // ITERATOR_HPP
