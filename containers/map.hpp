#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <functional>
# include <stdexcept>
# include "../utils/iterator_traits.hpp"
# include "../utils/pair.hpp"
# include "../iterators/map_iterator.hpp"
// # include "../iterators/reverse_iterator.hpp"
# include "../utils/BinaryTree.hpp"

namespace ft
{
	template <	class Key, class T,
				class Compare = std::less<Key>, 
				class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	private:
		typedef typename	ft::BinaryTree<Key, T, Compare, Alloc>			bt_type;
		typedef typename	bt_type::node_type								node_type;
	public:
		typedef				Key												key_type;
		typedef				T												mapped_type;
		typedef typename	ft::pair<const key_type, mapped_type>			value_type;
		typedef				Compare											key_compare;
		typedef				Alloc											allocator_type;
		typedef typename	allocator_type::reference						reference;
		typedef typename	allocator_type::const_reference					const_reference;
		typedef typename	allocator_type::pointer							pointer;
		typedef typename	allocator_type::const_pointer					const_pointer;
		typedef				map_iterator<value_type, node_type>				iterator;
		typedef				map_iterator<const value_type, node_type>		const_iterator;
		/*typedef typename	ft::reverse_iterator<iterator>					reverse_iterator;
		typedef typename	ft::reverse_iterator<const_iterator>			const_reverse_iterator;*/
		typedef typename	ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef				size_t											size_type;
		
		class value_compare : std::binary_function<value_type, value_type, bool> {
			friend class map;
		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}
		public:
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const {
				return this->comp(x.first, y.first);
			}
		};

		// Constructors & Destructor
		explicit map(const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type())
		: bt(ft::make_pair(comp, alloc)) {}

		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		: bt(ft::make_pair(comp, alloc)) {
			for (InputIterator it = first; it != last; it++)
				bt.insert(*it);
		}

		map(const map& x) : bt(x.bt) {
			*this = x;
		}

		map& operator=(const map& x) {
			this->bt = x.bt;
			return *this;
		}

		~map() {}

		// Iterators
		iterator begin() {
			return iterator(this->bt.begin());
		}
		const_iterator begin() const {
			const_iterator ret(this->bt.begin());
			return ret;
		}
		iterator end() {
			return iterator(this->bt.end());
		}
		const_iterator end() const {
			const_iterator ret(this->bt.end());
			return ret;
		}

		// Capacity
		bool empty() const {
			return (this->bt.size() == 0);
		}
		size_type size() const {
			return this->bt.size();
		}
		size_type max_size() const {
			return this->alloc.max_size();
		}

		// Element access
		mapped_type& operator[](const key_type& k) {
			node_type *p = this->bt.find(k);
			if (!p)
				p = this->bt.insert(ft::make_pair(k, mapped_type()));
			value_type& val = **p;
			return val.second;
		}
		mapped_type& at(const key_type& k) {
			node_type *p = this->bt.find(k);
			if (!p)
				throw std::out_of_range("map::at");
			value_type& val = **p;
			return val.second;
		}
		const mapped_type& at(const key_type& k) const {
			node_type *p = this->bt.find(k);
			if (!p)
				throw std::out_of_range("map::at");
			value_type& val = **p;
			return val.second;
		}

		// Modifiers
		ft::pair<iterator, bool> insert(const value_type& val) {
			node_type *p = this->bt.find(val.first);
			bool newElement = (p == NULL);
			if (newElement)
				p = this->bt.insert(val);
			return ft::make_pair(iterator(p), newElement);
		}
		iterator insert(iterator position, const value_type& val) {
			value_type pos_val = *position;
			node_type *p;
			if ((p = this->bt.find(val.first)))
				return iterator(p);
			p = this->bt.find(pos_val.first);
			if (p) {
				bool goodHint = true;
				position--;
				if (position->first > val.first)
					goodHint = false;
				position++;
				position++;
				if (position->first < val.first)
					goodHint = false;
				position--;
				if (goodHint) {
					p = p->add(val);
					return iterator(p);
				}
			}
			p = this->bt.insert(val);
			return iterator(p);
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last) {
			for (InputIterator it = first; it != last; it++)
				this->bt.insert(*it);
		}

		void erase(iterator position) {
			this->bt.erase(position->first);
		}
		size_type erase(const key_type& k) {
			if (this->bt.erase(k))
				return 1;
			return 0;
		}
		void erase(iterator first, iterator last) {
			for (iterator it = first; it != last; it++)
				this->bt.erase(it->first);
		}

		void swap(map& x) {
			bt_type tmp = this->bt;
			this->bt = x.bt;
			x.bt = tmp;
		}

		void clear() {
			this->bt.clear();
		}

		// Observers
		key_compare key_comp() const {
			return this->bt.get_map_traits().first;
		}

		value_compare value_comp() const {
			value_compare val_comp(this->key_comp());
			return val_comp;
		}

		// Operations
		iterator find(const key_type& k) {
			node_type *p = this->bt.find(k);
			return iterator(p);
		}
		const_iterator find(const key_type& k) const {
			node_type *p = this->bt.find(k);
			return const_iterator(p);
		}

		size_type count(const key_type& k) const {
			if (this->bt.find(k))
				return 1;
			return 0;
		}

		iterator lower_bound(const key_type& k) {
			key_compare comp = this->key_comp();
			for (iterator it = this->begin(); it != this->end(); it++)
				if (!comp(it->first, k))
					return it;
			return this->end();
		}
		const_iterator lower_bound(const key_type& k) const {
			key_compare comp = this->key_comp();
			for (const_iterator it = this->begin(); it != this->end(); it++)
				if (!comp(it->first, k))
					return it;
			return this->end();
		}

		iterator upper_bound(const key_type& k) {
			key_compare comp = this->key_comp();
			for (iterator it = this->begin(); it != this->end(); it++)
				if (comp(k, it->first))
					return it;
			return this->end();
		}
		const_iterator upper_bound(const key_type& k) const {
			key_compare comp = this->key_comp();
			for (const_iterator it = this->begin(); it != this->end(); it++)
				if (comp(k, it->first))
					return it;
			return this->end();
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
			node_type *p = this->bt.find(k);
			if (!p)
				return ft::make_pair(this->end(), this->end());
			const_iterator begin(p);
			const_iterator end(p);
			end++;
			return ft::make_pair(begin, end);
		}
		ft::pair<iterator, iterator> equal_range(const key_type& k) {
			node_type *p = this->bt.find(k);
			if (!p)
				return ft::make_pair(this->end(), this->end());
			iterator begin(p);
			iterator end(p);
			end++;
			return ft::make_pair(begin, end);
		}

		// Allocator
		allocator_type get_allocator() const {
			return this->bt.get_map_traits().second;
		}

	private:
		bt_type bt;
	};
}

#endif // MAP_HPP
