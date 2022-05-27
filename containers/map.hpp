#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <functional>
# include "../utils/iterator_traits.hpp"
# include "../utils/pair.hpp"
# include "../iterators/map_iterator.hpp"
// # include "../iterators/reverse_iterator.hpp"

namespace ft
{
	template <	class Key, class T,
				class Compare = std::less<Key>, 
				class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef				Key												key_type;
		typedef				T												mapped_type;
		typedef typename	ft::pair<const key_type, mapped_type>			value_type;
		typedef				Compare											key_compare;
		//typedef 															value_compare;
		typedef				Alloc											allocator_type;
		typedef typename	allocator_type::reference						reference;
		typedef typename	allocator_type::const_reference					const_reference;
		typedef typename	allocator_type::pointer							pointer;
		typedef typename	allocator_type::const_pointer					const_pointer;
		typedef				map_iterator<value_type>						iterator;
		typedef				map_iterator<const value_type>					const_iterator;
		/*typedef typename	ft::reverse_iterator<iterator>					reverse_iterator;
		typedef typename	ft::reverse_iterator<const_iterator>			const_reverse_iterator;*/
		typedef typename	ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef				size_t											size_type;

	private:
	};
}

#endif // MAP_HPP
