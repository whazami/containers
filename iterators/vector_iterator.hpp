/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:38:23 by whazami           #+#    #+#             */
/*   Updated: 2022/05/18 01:15:59 by whazami          ###   ########.fr       */
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
		void	operator++(int) {
			this->p++;
		}
		difference_type	operator-(vector_iterator rhs) {
			return this->p - rhs.p;
		}
		bool	operator!=(vector_iterator rhs) {
			if (this->p != rhs.p)
				return true;
			return false;
		}

	private:
		pointer	p;	
	};
}

#endif // ITERATOR_HPP
