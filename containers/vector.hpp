#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <stdexcept>
# include <typeinfo>
# include "../iterators/vector_iterator.hpp"
# include "../iterators/reverse_iterator.hpp"
# include "../utils/iterator_traits.hpp"
# include "../utils/lexicographical_compare.hpp"
# include "../utils/enable_if.hpp"
# include "../utils/is_integral.hpp"

namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef 			T												value_type;
			typedef 			Alloc											allocator_type;
			typedef	typename	allocator_type::reference						reference;
			typedef typename	allocator_type::const_reference					const_reference;
			typedef	typename	allocator_type::pointer							pointer;
			typedef typename	allocator_type::const_pointer					const_pointer;
			typedef 			vector_iterator<value_type>						iterator;
			typedef 			vector_iterator<const value_type>				const_iterator;
			typedef 			ft::reverse_iterator<iterator>					reverse_iterator;
			typedef				ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename	ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef 			size_t											size_type;
			

			// Constructors & Destructor
			explicit vector(const allocator_type& alloc = allocator_type())
				: arr(NULL), alloc(alloc), sizee(0), capacityy(0), old_resize(0){}

			explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) 
				: arr(NULL), alloc(alloc), sizee(0), capacityy(0), old_resize(0){
					this->assign(n, val);
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
				: arr(NULL), alloc(alloc), sizee(0), capacityy(0), old_resize(0) {
					this->assign(first, last);
				}
			
			vector (const vector &x) : arr(NULL), sizee(0), capacityy(0), old_resize(0) {
				*this = x;
			}
						
			~vector() {
				if (this->arr != NULL) {
					for (size_type i = 0; i < this->sizee; i++)
						this->alloc.destroy(&this->arr[i]);
					this->alloc.deallocate(this->arr, this->capacityy);
				}
			}
			
			vector& operator=(const vector& x) {
				if (this != &x)
					this->assign(x.begin(), x.end());
				return *this;
			}

			// Iterators
			iterator begin() {
				return iterator(this->arr);
			}
			
			const_iterator begin() const {
				return const_iterator(this->arr);
			}

			iterator end() {
				return iterator(arr + this->sizee);
			}

			const_iterator end() const {
				return const_iterator(this->arr + this->sizee);
			}

			reverse_iterator rbegin() {
				return reverse_iterator(this->end());
			}

			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(this->end());
			}

			reverse_iterator rend() {
				return reverse_iterator(this->begin());
			}

			const_reverse_iterator rend() const {
				return const_reverse_iterator(this->begin());
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
						if (n <= this->old_resize || n > this->old_resize * 2)
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
				return this->sizee == 0;
			}

			void reserve(size_type n) {
				if (n > this->max_size())
					throw(std::length_error("vector::reserve"));
				if (this->capacityy >= n)
					return ;
				size_type	new_capacity = n;
				this->reallocate(new_capacity);
			}
			
			// Element Access
			reference operator[] (size_type n) {
				return this->arr[n]; 
			}
			
			const_reference operator[] (size_type n) const{
				return this->arr[n]; 
			}

			reference at(size_type n) {
				if (n >= this->sizee)
					throw std::out_of_range(this->out_of_range_what(n));
				return this->arr[n];
			}

			const_reference at(size_type n) const {
				if (n >= this->sizee)
					throw std::out_of_range(this->out_of_range_what(n));
				return this->arr[n];
			}

			reference front() {
				return this->arr[0];
			}
			
			const_reference front() const {
				return this->arr[0];
			}
			
			reference back() {
				return this->arr[sizee - 1];
			}
			
			const_reference back() const {
				return this->arr[sizee - 1];
			}

			value_type* data() {
				return this->arr;
			}

			const value_type* data() const {
				return this->arr;
			}

			// Modifiers
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last, 
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)  {
				size_type new_size = 0;
				size_type i = 0;
				InputIterator it = first;

				while (it != last) {
					new_size++;
					it++;
				}
				this->reserve(new_size);

				if (new_size < this->sizee) {
					while (i < new_size) {
						this->alloc.destroy(this->arr + i);
						this->alloc.construct(this->arr + i, *first++);
						i++;
					}
					while (i < this->sizee) {
						this->alloc.destroy(this->arr + i);
						i++;
					}
				} else {
					while (i < this->sizee) {
						this->alloc.destroy(this->arr + i);
						this->alloc.construct(this->arr + i, *first++);
						i++;
					}
					while (i < new_size) {
						this->alloc.construct(this->arr + i, *first++);
						i++;
					}
				}
				this->sizee = new_size;
			}

			void assign(size_type n, const value_type& val) {
				this->reserve(n);
				size_type i = 0;

				if (n < this->sizee) {
					while (i < n) {
						this->alloc.destroy(this->arr + i);
						this->alloc.construct(this->arr + i, val);
						i++;
					}
					while (i < this->sizee) {
						this->alloc.destroy(this->arr + i);
						i++;
					}
				}
				else {
					while (i < this->sizee) {
						this->alloc.destroy(this->arr + i);
						this->alloc.construct(this->arr + i, val);
						i++;
					}
					while (i < n) {
						this->alloc.construct(this->arr + i, val);
						i++;
					}
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
				}
				this->alloc.construct(this->arr + this->sizee, val);
				this->sizee++;
			}

			void pop_back() {
				this->erase(this->end() - 1);
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
				if (n) {
					size_type id = position - this->begin();
					if (this->sizee + n > this->capacityy) {
						if (this->sizee * 2 > this->sizee + n)
							this->reallocate(this->sizee * 2);
						else
							this->reallocate(this->sizee + n);
					}
					if (this->empty()) {
						for (size_type i = 0; i < n; i++)
							this->alloc.construct(this->arr + i, val);
						this->sizee += n;
					}
					else {
						for (size_type i = this->sizee + n - 1; i >= id + n; i--) {
							if (i >= this->sizee)
								this->alloc.construct(this->arr + i, this->arr[i - n]);
							else
								this->arr[i] = this->arr[i - n];
						}
						for (size_type i = 0; i < n; i++) {
							if (id + i < this->sizee) {
								this->alloc.destroy(this->arr + id + i);
								this->alloc.construct(this->arr + id + i, val);
							}
							else
								this->alloc.construct(this->arr + id + i, val);
						}
						this->sizee += n;
					}
				}
			}

			template<class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
				size_type id = position - this->begin();
				size_type new_size = 0;
				for (InputIterator it = first; it != last; it ++)
					new_size++;
				if (this->sizee + new_size > this->capacityy)
					this->reallocate(this->sizee * 2 + new_size);
				if (this->empty()) {
					size_type i = 0;
					for (InputIterator it = first; it != last; it++, i++)
						this->alloc.construct(this->arr + i, *it);
					this->sizee += new_size;
				}
				else {
					for (size_type i = this->sizee + new_size - 1; i >= id + new_size; i--)
					if (i >= this->sizee)
							this->alloc.construct(this->arr + i, this->arr[i - new_size]);
						else
							this->arr[i] = this->arr[i - new_size];
					size_type i = 0;
					for (InputIterator it = first; it != last; it ++, i++) {
						if (id + i < this->sizee) {
							this->alloc.destroy(this->arr + id + i);
							this->alloc.construct(this->arr + id + i, *it);
						}
						else {
							this->alloc.construct(this->arr + id + i, *it);
						}
					}
					this->sizee += new_size;
				}
			}

			iterator erase(iterator position) {
				return (this->erase(position, position + 1));
			}

			iterator erase(iterator first, iterator last) {
				if (first == this->end() || first == last)
					return first;

				size_type begin = 0;
				size_type first_to_last = 0;
				size_type last_to_end = 0;
				size_type i = 0;

				iterator it = this->begin();

				while (it != first) {
					begin++;
					it++;
				}
				it = first;
				while (it != last) {
					first_to_last++;
					it ++;
				}

				it = last;
				while (it != this->end()) {
					last_to_end++;
					it++;
				}

				while (i < last_to_end) {
					this->alloc.destroy(&this->arr[begin + i]);
					this->alloc.construct(&this->arr[begin + i], this->arr[begin + i + first_to_last]);
					i++;
				}

				i = 0;
				while (i < first_to_last) {
					this->alloc.destroy(&this->arr[begin + last_to_end + i]);
					i++;
				}
				this->sizee -= first_to_last;
				return first;
			}

			void swap(vector& x) {
				pointer tmp = this->arr;
				this->arr = x.arr;
				x.arr = tmp;
				size_type tmp_size = this->sizee;
				this->sizee = x.sizee;
				x.sizee = tmp_size;
				size_type tmp_capacity = this->capacityy;
				this->capacityy = x.capacityy;
				x.capacityy = tmp_capacity;
			}

			void clear() {
				for (size_type i = 0; i < this->sizee; i++)
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
			size_type		capacityy;	// same
			size_type		old_resize;

			// Get the error message for out_of_range exception
			std::string out_of_range_what(size_type n) const {
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

			// Allocation Manager
			void allocate(size_type n) {
				if (n > this->max_size())
					throw std::length_error("vector::reserve");
				this->arr = NULL;
				if (n > this->capacityy) {
					this->arr = this->alloc.allocate(n);
					this->capacityy = n;
				}
			}

			void deallocate() {
				this->deallocate(this->arr, this->capacityy);
				this->capacityy = 0;
			}

			void deallocate(pointer p, size_type capacity) {
				for (size_type i = 0; i < this->sizee; i++)
					this->alloc.destroy(p + i);
				if (p)
					this->alloc.deallocate(p, capacity);
			}

			void reallocate(size_type new_capacity) {
				pointer tmp = this->alloc.allocate(new_capacity);
				for (size_type i = 0; i < this->sizee; i++) {
					this->alloc.construct(tmp + i, this->arr[i]);
					this->alloc.destroy(&this->arr[i]);
				}
				this->alloc.deallocate(this->arr, this->capacityy);
				this->arr = tmp;
				this->capacityy = new_capacity;
			}
	};

	// Relational Operators
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
