#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <stdexcept>
# include <typeinfo>
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
		explicit vector(const allocator_type& alloc = allocator_type())
						: arr(NULL), alloc(alloc), sizee(0), capacity(0) {}

		explicit vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
						: arr(NULL), alloc(alloc), sizee(0), capacity(0) {
			this->assign(n, val);
		}

		// Needs enable_if
		/*template <class InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type()) {
			this->alloc = alloc;
			this->sizee = 0;
			for (InputIterator it = first; it != last; it++)
				this->sizee++;
			this->arr = (this->sizee != 0) ? this->alloc.allocate(this->sizee) : NULL;
			this->capacity = this->sizee;
			size_type i = 0;
			for (InputIterator it = first; it != last; it++, i++)
				this->alloc.construct(arr + i, *it);
		}*/

		vector (const vector &x) : arr(NULL), sizee(0), capacity(0) {
			*this = x;
		}

		~vector() {
			this->deallocate();
		}
		
		vector	&operator=(const vector& x) {
			this->deallocate();
			this->arr = (x.sizee != 0) ? this->alloc.allocate(x.sizee) : NULL;
			this->capacity = x.sizee;
			for (size_type i = 0; i < x.sizee; i++)
				this->alloc.construct(arr + i, x.arr[i]);
			this->sizee = x.sizee;
			return *this;
		}

		// Iterators
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

		// Capacity
		size_type size() const {
			return sizee;
		}

		bool empty() const {
			if (sizee == 0)
				return true;
			return false;
		}

		// Element access
		reference operator[] (size_type n) {
			return arr[n]; 
		}
		const_reference operator[] (size_type n) const {
			return arr[n];
		}
		
		reference at(size_type n) {
			if (n >= this->sizee)
				throw std::out_of_range(this->oor_what(n));
			return arr[n];
		}
		const_reference at(size_type n) const {
			if (n >= this->sizee)
				throw std::out_of_range(this->oor_what(n));
			return arr[n];
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

		// Modifiers
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last) {	// same as range constructor
			this->deallocate();									// only this line changes
			this->sizee = 0;
			for (InputIterator it = first; it != last; it++)
				this->sizee++;
			this->arr = (this->sizee != 0) ? this->alloc.allocate(this->sizee) : NULL;
			this->capacity = this->sizee;
			size_type i = 0;
			for (InputIterator it = first; it != last; it++, i++)
				this->alloc.construct(arr + i, *it);
		}
		void assign(size_type n, const value_type& val) {	// same as fill constructor
			this->deallocate();								// only this line changes
			this->arr = (n != 0) ? this->alloc.allocate(n) : NULL;
			this->capacity = n;
			this->sizee = n;
			for (size_type i = 0; i < n; i++)
				this->alloc.construct(arr + i, val);
		}

		void push_back(const value_type& val) {
			if (this->sizee + 1 > this->capacity) {
				size_type new_capacity = this->capacity;
				if (new_capacity == 0)
					new_capacity = 1;
				else
					new_capacity *= 2;
				this->reallocate(new_capacity);
				this->alloc.construct(this->arr + this->sizee, val);
			}
			else
				this->alloc.construct(this->arr + this->sizee, val);
			this->sizee++;
		}

		void pop_back() {
			
		}

		void reserve(size_type n) {
			size_type max_size = 80000000; // provisoire
			if (n > max_size)
				throw std::length_error("blabla");
			if (this->capacity >= n)
				return ;
			this->reallocate(n);
		}

		size_type c() {
			return this->capacity;
		}

	private:
		pointer			arr;
		allocator_type	alloc;
		size_type		sizee;		// cause size already taken by method
		size_type		capacity;	// allocated size of the vector

		void deallocate() {
			this->deallocate(this->arr, this->capacity);
		}
		void deallocate(pointer p, size_type capacity) {
			for (size_t i = 0; i < this->sizee; i++)
				this->alloc.destroy(p + i);
			if (p)
				this->alloc.deallocate(p, capacity);
		}

		void reallocate(size_type new_capacity) {
			// On cree un pointeur tmp qui est une copie de arr
			pointer tmp = (this->sizee != 0) ? this->alloc.allocate(this->sizee) : NULL;
			for (size_t i = 0; i < this->sizee; i++)
				this->alloc.construct(tmp + i, this->arr[i]);
			this->deallocate();
			this->arr = this->alloc.allocate(new_capacity);
			for (size_t i = 0; i < this->sizee; i++)
				this->alloc.construct(this->arr + i, tmp[i]);
			this->deallocate(tmp, this->sizee);
			this->capacity = new_capacity;
		}

		// Get the error message for out_of_range exception
		std::string	oor_what(size_type n) const {
			std::stringstream ss;
			std::string what = "vector::_M_range_check: __n (which is ";
			ss << n;
			what.append(ss.str());
			what.append(") >= this->size() (which is ");
			ss.str("");
			ss << this->size();
			what.append(ss.str());
			what.push_back(')');
			return what;
		}
	};
}

#endif // VECTOR_HPP
