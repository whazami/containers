#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "../iterators/vector_iterator.hpp"

namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef 			T									value_type;
			typedef 			Alloc								allocator_type;
			typedef	typename	allocator_type::reference			reference;		
			typedef typename	allocator_type::const_reference		const_reference;
			typedef	typename	allocator_type::pointer				pointer;
			typedef typename	allocator_type::const_pointer		const_pointer;
			typedef 			vector_iterator<value_type>			iterator;
			typedef 			vector_iterator<const value_type>	const_iterator;
			typedef 			size_t								size_type;
			

			// Constructors & Destructor
			explicit vector(const allocator_type& alloc = allocator_type()) {
				this->alloc = alloc;
				this->arr = this->alloc.allocate(0);
				this->sizee = 0;	
			}

			explicit vector(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type()) {
				this->alloc = alloc;
				this->arr = this->alloc.allocate(n);
				this->sizee = n;
				for (size_type i = 0; i < this->sizee; i++)
					this->arr[i] = val;
			}

			/*template <class InputIterator>
			vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type()) {
				this->alloc = alloc;
				this->sizee = last - first;
				this->arr = this->alloc.allocate(this->sizee);
				size_type i = 0;
				for (InputIterator it = first; it != last; it++, i++)
					this->arr[i] = *it;
			}*/

			vector (const vector &x) {
				this->arr = this->alloc.allocate(0);
				*this = x;
			}

			~vector() {
				this->alloc.deallocate(this->arr, this->sizee);
			}
			
			// Methods
			iterator begin() {
				return iterator(arr);
			}
			const_iterator begin() const {
				const_iterator ret(arr);
				return ret;
			}
			iterator end() {
				return iterator(arr + sizee);
			}
			const_iterator end() const {
				const_iterator ret(arr + sizee);
				return ret;
			}

			reference front() {
				return arr[0];
			}
			const_reference front() const {
				return arr[0];
			}
			reference back() {
				return arr[sizee - 1];
			}
			const_reference back() const {
				return arr[sizee - 1];
			}

			size_type size() const {
				return sizee;
			}

			bool empty() const {
				if (sizee == 0)
					return true;
				return false;
			}

			// Operators
			vector	&operator=(const vector& x) {
				this->alloc.deallocate(this->arr, this->sizee);
				this->arr = this->alloc.allocate(x.sizee);
				for (size_type i = 0; i < x.sizee; i++)
					this->arr[i] = x.arr[i];
				this->sizee = x.sizee;
				return *this;
			}

			reference operator[] (size_type n) {
				return arr[n]; 
			}
			const_reference operator[] (size_type n) const {
				return arr[n];
			}
			
		private:
			pointer			arr;
			allocator_type	alloc;
			size_type		sizee;	// cause size already taken by method
	};
}

#endif // VECTOR_HPP
