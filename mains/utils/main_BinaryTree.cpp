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
	
	std::cout << std::boolalpha;

	{
	std::cout << "Offset: 2" << std::endl;
	binary_tree_type bt(ft::make_pair(std::less<FIRST_TYPE>(), alloc));
	std::cout << bt.size() << std::endl;
	for (FIRST_TYPE c = 'c'; c < 'z'; c += 2)
		bt.insert(ft::make_pair(c, 42 + c));
	std::cout << bt.size() << std::endl;
	bt.insert(ft::make_pair('b', 21));
	bt.insert(ft::make_pair('f', 41));
	bt.insert(ft::make_pair('f', 49));
	std::cout << bt.size() << std::endl;
	binary_tree_type::node_type *node = bt.find('f');
	std::cout << (*node)->second << std::endl;
	node = bt.find('a');
	if (node)
		std::cout << (*node)->second << std::endl;
	node = bt.find('c');
	std::cout << bt.size() << std::endl;
	std::cout << (*node)->second << std::endl;
	bt.erase('b'); // No children case
	bt.erase('m'); // only right case
	std::cout << bt.erase('g') << std::endl; // left case
	std::cout << bt.erase('g') << std::endl; // should print false
	bt.erase('y'); // leaf case
	if (!bt.find('g'))
		std::cout << "yess" << std::endl;
	std::cout << std::endl;
	std::cout << bt.size() << std::endl;
	}

	{
	std::cout << "Offset: 4" << std::endl;
	binary_tree_type bt(ft::make_pair(std::less<FIRST_TYPE>(), alloc));
	std::cout << bt.size() << std::endl;
	for (FIRST_TYPE c = 'c'; c < 'z'; c += 4)
		bt.insert(ft::make_pair(c, 42 + c));
	std::cout << bt.size() << std::endl;
	bt.erase('w'); // No children case
	bt.erase('g'); // Only right case
	std::cout << bt.size() << std::endl;
	bt.insert(ft::make_pair('q', 42));
	bt.erase('s'); // Only left case
	bt.insert(ft::make_pair('m', 42));
	bt.erase('o'); // Left & Right
	std::cout << bt.size() << std::endl;
	bt.insert(ft::make_pair('A', 42));
	bt.insert(ft::make_pair('M', 42));
	bt.insert(ft::make_pair('O', 42));
	bt.insert(ft::make_pair('U', 42));
	bt.insert(ft::make_pair('R', 42));
	bt.erase('c'); // Left then right (have left) (and root btw)
	bt.erase('U'); // Left then right (dont have left)
	std::cout << bt.size() << std::endl;
	std::cout << (bt.find('w') == NULL ? "✅" : "❌") << std::endl;
	std::cout << (bt.find('g') == NULL ? "✅" : "❌") << std::endl;
	std::cout << (bt.find('s') == NULL ? "✅" : "❌") << std::endl;
	std::cout << (bt.find('o') == NULL ? "✅" : "❌") << std::endl;
	std::cout << (bt.find('c') == NULL ? "✅" : "❌") << std::endl;
	std::cout << (bt.find('U') == NULL ? "✅" : "❌") << std::endl;
	std::cout << (bt.find('U') == NULL ? "✅" : "❌") << std::endl;
	std::cout << (bt.find('A') != NULL ? "✅" : "❌") << std::endl;
	std::cout << (bt.find('R') != NULL ? "✅" : "❌") << std::endl;
	std::cout << (bt.find('q') != NULL ? "✅" : "❌") << std::endl;
	std::cout << (bt.find('k') != NULL ? "✅" : "❌") << std::endl;
	std::cout << (bt.find('k') != NULL ? "✅" : "❌") << std::endl;
	std::cout << bt.size() << std::endl;
	std::cout << std::endl;
	}

	std::cout << "--- Special root cases ---" << std::endl;
	{
	binary_tree_type bt(ft::make_pair(std::less<FIRST_TYPE>(), alloc));
	std::cout << "erasing root..." << std::endl;
	std::cout << bt.size() << std::endl;
	bt.insert(ft::make_pair('a', 42));
	std::cout << bt.size() << std::endl;
	bt.erase('a');
	std::cout << bt.size() << std::endl;
	std::cout << bt.erase(' ') << std::endl;
	std::cout << (bt.find(' ') != NULL) << std::endl;
	std::cout << std::endl;
	}
	{
	binary_tree_type bt(ft::make_pair(std::less<FIRST_TYPE>(), alloc));
	std::cout << "erasing root with left child..." << std::endl;
	std::cout << bt.size() << std::endl;
	bt.insert(ft::make_pair('a', 42));
	bt.insert(ft::make_pair('A', 42));
	std::cout << bt.size() << std::endl;
	bt.erase('a');
	std::cout << bt.size() << std::endl;
	std::cout << bt.erase(' ') << std::endl;
	std::cout << (bt.find('A') != NULL) << std::endl;
	std::cout << std::endl;
	}
	{
	binary_tree_type bt(ft::make_pair(std::less<FIRST_TYPE>(), alloc));
	std::cout << "erasing root with right child..." << std::endl;
	std::cout << bt.size() << std::endl;
	bt.insert(ft::make_pair('a', 42));
	bt.insert(ft::make_pair('z', 42));
	std::cout << bt.size() << std::endl;
	bt.erase('a');
	std::cout << bt.size() << std::endl;
	std::cout << bt.erase('a') << std::endl;
	std::cout << (bt.find('z') != NULL) << std::endl;
	}
	return 0;
}
