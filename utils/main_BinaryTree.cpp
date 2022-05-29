#include <iostream>
#include "BinaryTree.hpp"
#include "pair.hpp"

#define FIRST_TYPE char
#define SECOND_TYPE int

int main()
{
	typedef std::allocator<ft::pair<const FIRST_TYPE, SECOND_TYPE> > allocator_type;
	allocator_type alloc;
	typedef ft::BinaryTree<FIRST_TYPE, SECOND_TYPE, std::less<FIRST_TYPE>, allocator_type > binary_tree_type;
	binary_tree_type bt(ft::make_pair(std::less<FIRST_TYPE>(), alloc));

	for (FIRST_TYPE c = 'c'; c < 'z'; c += 4)
		bt.insert(ft::make_pair(c, 42 + c));
	// Offset: 2
	/*bt.insert(ft::make_pair('b', 21));
	bt.insert(ft::make_pair('f', 41));
	bt.insert(ft::make_pair('f', 49));
	binary_tree_type::node_type *node = bt.find('f');
	std::cout << **node << std::endl;
	node = bt.find('a');
	if (node)
		std::cout << **node << std::endl;
	node = bt.find('c');
	std::cout << **node << std::endl;
	std::cout << std::endl;
	bt.erase('b'); // No children case
	bt.erase('m'); // only right case
	bt.erase('g'); // left case
	bt.erase('y'); // leaf case*/

	// Offset: 4
	bt.erase('w'); // No children case
	bt.erase('g'); // Only right case
	bt.insert(ft::make_pair('q', 42));
	bt.erase('s'); // Only left case
	bt.insert(ft::make_pair('m', 42));
	bt.erase('o'); // Left & Right
	bt.insert(ft::make_pair('A', 42));
	bt.insert(ft::make_pair('M', 42));
	bt.insert(ft::make_pair('O', 42));
	bt.insert(ft::make_pair('U', 42));
	bt.insert(ft::make_pair('R', 42));
	bt.erase('c'); // Left then right (have left)
	bt.erase('U'); // Left then right (dont have left)
	return 0;
}
