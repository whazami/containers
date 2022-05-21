/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:38:23 by whazami           #+#    #+#             */
/*   Updated: 2022/05/21 22:03:13 by whazami          ###   ########.fr       */
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

		// Operators
		value_type	operator*() const {
			return *this->p;
		}
		vector_iterator &operator++() { // pre incrementation
			this->p++;
			return *this;
		}
		vector_iterator	operator++(int) { // post incrementation
			vector_iterator tmp(*this);
			this->operator++();
			return tmp;
		}
		vector_iterator operator+(int n) {
			return this->p + n;
		}
		difference_type	operator-(vector_iterator rhs) {
			return this->p - rhs.p;
		}
		vector_iterator operator-(int n) {
			return this->p - n;
		}
		bool	operator==(vector_iterator rhs) {
			if (this->p == rhs.p)
				return true;
			return false;
		}
		bool	operator!=(vector_iterator rhs) {
			return !(*this == rhs);
		}
		void print() {
			std::cout << this->p << std::endl;
		}

	private:
		pointer	p;	
	};
}

#endif // ITERATOR_HPP
