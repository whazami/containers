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
		typedef typename	std::iterator_traits<iterator>::difference_type	difference_type;
		typedef 			size_t								size_type;
		

		// Constructors & Destructor
		explicit vector(const allocator_type& alloc = allocator_type())
						: arr(NULL), alloc(alloc), sizee(0), capacityy(0), old_resize(0) {}

		explicit vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
						: arr(NULL), alloc(alloc), sizee(0), capacityy(0), old_resize(0) {
			this->assign(n, val);
		}

		// Needs enable_if
		/*template <class InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type())
				: arr(NULL), alloc(alloc), sizee(0), capacityy(0), old_resize(0) {
				this->assign(first, last);
		}*/

		vector (const vector &x) : arr(NULL), sizee(0), capacityy(0), old_resize(0) {
			*this = x;
		}

		~vector() {
			this->deallocate();
		}
		
		vector	&operator=(const vector& x) {
			this->deallocate();
			this->allocate(x.sizee);
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
			return this->sizee;
		}

		size_type max_size() const {
			return this->alloc.max_size();
		}

		void resize(size_type n, value_type val = value_type()) {
			if (n < this->sizee)
				for (size_t i = n; i < this->sizee; i++)
					this->alloc.destroy(this->arr + i);
			else {
				if (n > this->capacityy) {
					size_type new_capacity;
					if (this->old_resize == 0 || n > this->old_resize * 2)
						new_capacity = n;
					else
						new_capacity = this->old_resize * 2;
					this->reallocate(new_capacity);
				}
				for (size_type i = this->sizee; i < n; i++)
					this->alloc.construct(this->arr + i, val);
			}
			this->sizee = n;
			this->old_resize = n;
		}

		size_type capacity() const {
			return this->capacityy;
		}

		bool empty() const {
			if (sizee == 0)
				return true;
			return false;
		}

		void reserve(size_type n) {
			if (this->capacityy >= n)
				return ;
			this->reallocate(n);
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

		value_type* data() {
			return this->arr;
		}
		const value_type* data() const {
			return this->arr;
		}

		// Modifiers
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last) {
			size_t new_size = 0;
			for (InputIterator it = first; it != last; it++)
				new_size++;
			if (new_size > this->capacityy) {
				this->deallocate();
				this->allocate(new_size);
				size_type i = 0;
				for (InputIterator it = first; it != last; it++, i++)
					this->alloc.construct(arr + i, *it);
			} else {
				size_type i = 0;
				for (InputIterator it = first; it != last; it++, i++) {
					this->alloc.destroy(arr + i);
					this->alloc.construct(arr + i, *it);
				}
			}
			this->sizee = new_size;
		}
		void assign(size_type n, const value_type& val) {
			if (n > this->capacityy) {
				this->deallocate();
				this->allocate(n);
				for (size_type i = 0; i < n; i++)
					this->alloc.construct(arr + i, val);
			} else
				for (size_type i = 0; i < n; i++) {
					this->alloc.destroy(arr + i);
					this->alloc.construct(arr + i, val);
				}
			this->sizee = n;
		}

		void push_back(const value_type& val) {
			if (this->sizee + 1 > this->capacityy) {
				size_type new_capacity = this->capacityy;
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
			this->alloc.destroy(this->arr + this->size() - 1);
			this->sizee--;
		}

		iterator insert(iterator position, const value_type& val) {
			size_type id = position - this->begin();
			if (this->sizee + 1 > this->capacityy)
				this->reallocate(this->sizee + 1);
			if (this->empty()) {
				this->alloc.construct(this->arr, val);
				this->sizee++;
				return this->begin();
			}
			for (size_type i = this->sizee; i > id; i--)
				this->arr[i] = this->arr[i - 1];
			this->alloc.construct(this->arr + id, val);
			this->sizee++;
			return this->begin() + id;
		}
		void insert(iterator position, size_type n, const value_type& val) {
			size_type id = position - this->begin();
			if (this->sizee + n > this->capacityy)
				this->reallocate(this->sizee + n);
			if (this->empty()) {
				for (size_type i = 0; i < n; i++)
					this->alloc.construct(this->arr + i, val);
				this->sizee += n;
				return ;
			}
			for (size_type i = this->sizee + n - 1; i >= n; i--)
				this->arr[i] = this->arr[i - n];
			for (size_type i = 0; i < n; i++)
				this->alloc.construct(this->arr + id + i, val);
			this->sizee += n;
		}
		/*template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last) {
			size_type id = position - this->begin();
			size_type extra_size = 0;
			for (InputIterator it = first; it != last; it++)
				extra_size++;
			if (this->sizee + extra_size > this->capacityy)
				this->reallocate(this->sizee + extra_size);
			if (this->empty()) {
				size_type i = 0;
				for (InputIterator it = first; it != last; it++, i++)
					this->alloc.construct(this->arr + i, *it);
				this->sizee += extra_size;
				return ;
			}
			for (size_type i = this->sizee + extra_size - 1; i >= extra_size; i--)
				this->arr[i] = this->arr[i - extra_size];
			size_type i = 0;
			for (InputIterator it = first; it != last; it++, i++)
				this->alloc.construct(this->arr + id + i, *it);
			this->sizee += extra_size;
		}*/

		iterator erase(iterator position) {
			size_type id = position - this->begin();
			this->alloc.destroy(this->arr + id);
			for (size_type i = id; i < this->sizee - 1; i++)
				this->arr[i] = this->arr[i + 1];
			this->sizee--;
			return this->begin() + id;
		}
		iterator erase(iterator first, iterator last) {
			size_type size_loss = 0;
			for (iterator it = first; it != last; it++) {
				this->alloc.destroy(this->arr + (it - this->begin()));
				size_loss++;
			}
			for (size_type i = first - this->begin(); i < this->sizee - size_loss; i++)
				this->arr[i] = this->arr[i + size_loss];
			this->sizee -= size_loss;
			return this->begin() + (first - this->begin());
		}

		void swap(vector& x) {
			pointer tmp = (this->sizee != 0) ? this->alloc.allocate(this->sizee) : NULL;
			for (size_t i = 0; i < this->sizee; i++)
				this->alloc.construct(tmp + i, this->arr[i]);
			this->deallocate();
			this->allocate(x.sizee);
			for (size_t i = 0; i < x.sizee; i++)
				this->alloc.construct(this->arr + i, x.arr[i]);
			x.deallocate();
			x.allocate(this->sizee);
			for (size_t i = 0; i < this->sizee; i++)
				x.alloc.construct(x.arr + i, tmp[i]);
			this->deallocate(tmp, this->sizee);
			size_type tmp_size = this->sizee;
			this->sizee = x.sizee;
			x.sizee = tmp_size;
		}

		void clear() {
			for (size_t i = 0; i < this->sizee; i++)
				this->alloc.destroy(this->arr + i);
			this->sizee = 0;
		}

		// Allocator
		allocator_type get_allocator() const {
			return this->alloc;
		}

	private:
		pointer			arr;
		allocator_type	alloc;
		size_type		sizee;		// cause size already taken by method
		size_type		capacityy;	// cause capacity already taken by method
		size_type		old_resize;

		// Allocation manager
		void allocate(size_type n) {
			if (n > this->max_size())
				throw std::length_error("vector::reserve");
			this->arr = NULL;
			if (n > this->capacityy) {
				this->arr = (n != 0) ? this->alloc.allocate(n) : NULL;
				this->capacityy = n;
			}
		}

		void deallocate() {
			this->deallocate(this->arr, this->capacityy);
			this->capacityy = 0;
		}
		void deallocate(pointer p, size_type capacity) {
			for (size_t i = 0; i < this->sizee; i++)
				this->alloc.destroy(p + i);
			if (p)
				this->alloc.deallocate(p, capacity);
		}

		void reallocate(size_type new_capacity) {
			pointer tmp = (this->sizee != 0) ? this->alloc.allocate(this->sizee) : NULL;
			for (size_t i = 0; i < this->sizee; i++)
				this->alloc.construct(tmp + i, this->arr[i]);
			this->deallocate();
			this->allocate(new_capacity);
			for (size_t i = 0; i < this->sizee; i++)
				this->alloc.construct(this->arr + i, tmp[i]);
			this->deallocate(tmp, this->sizee);
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

	// Relational operators
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (typename vector<T>::size_type i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return !(rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return rhs < lhs;
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
		x.swap(y);
	}
}

#endif // VECTOR_HPP
