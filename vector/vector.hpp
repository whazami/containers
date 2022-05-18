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
			typedef 			size_t								size_type;
			

			// Constructors & Destructor
			explicit vector(const allocator_type& alloc = allocator_type()) {
				this->alloc = alloc;
				this->arr = this->alloc.allocate(0);
				this->_size = 0;	
			}

			explicit vector(size_type n, const value_type& val = value_type(),
								const allocator_type& alloc = allocator_type()) {
				this->alloc = alloc;
				this->arr = this->alloc.allocate(n);
				this->_size = n;
				for (size_type i = 0; i < this->_size; i++)
					this->arr[i] = val;
			}

			/*template <class InputIterator>
			vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type()) {
				this->alloc = alloc;
				this->_size = last - first;
				this->arr = this->alloc.allocate(this->_size);
				size_type i = 0;
				for (InputIterator it = first; it != last; it++, i++)
					this->arr[i] = *it;
			}*/

			vector (const vector &x) {
				this->arr = this->alloc.allocate(0);
				*this = x;	
			}

			~vector() {
				this->alloc.deallocate(this->arr, this->_size);
			}
			
			// Iterators
			iterator begin() {
				return iterator(&arr[0]);
			}
			
			iterator end() {
				return iterator(arr + _size);
			}

			// operator=()
			vector	&operator=(const vector& x) {
				this->alloc.deallocate(this->arr, this->_size);
				this->arr = this->alloc.allocate(x._size);
				for (size_type i = 0; i < x._size; i++)
					this->arr[i] = x.arr[i];
				this->_size = x._size;
				//this->alloc = x.alloc;
				return *this;
			}

			//operator[]()
			reference operator[] (size_type n) {
				//if (n > _size || n < 0)	
				return arr[n]; 
			}
			
			const_reference operator[] (size_type n) const{
				//if (n > _size || n < 0)	
				return arr[n]; 
			}
			
			// Front() et Back()
			reference front(){
				return arr[0];
			}
			const_reference front() const{
				return arr[0];
			}
			reference back(){
				return arr[_size - 1];
			}
			const_reference back() const{
				return arr[_size - 1];
			}

			// size()
			size_type size() const { //problem name size avec variable private donc ajout d'un _devant la variable size 
				return _size;
			}

			// empty()
			bool empty() const {
				if (_size == 0)
					return true;
				return false;
			}
		private:
			pointer			arr;
			allocator_type	alloc;
			size_type		_size;
	};
}

#endif // VECTOR_HPP
