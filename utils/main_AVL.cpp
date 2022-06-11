#include "AVL.hpp"
#include <iostream>

int main()
{
	typedef typename std::less<int> key_compare;
	typedef typename std::allocator<ft::pair<int, char> > allocator_type;
	key_compare comp;
	allocator_type alloc;
	ft::AVL<int, char, key_compare, allocator_type> avl(comp, alloc);

	avl.insert(ft::make_pair(33, 'c'));
	avl.insert(ft::make_pair(13, 'c'));
	avl.insert(ft::make_pair(53, 'c'));
	avl.insert(ft::make_pair(9, 'c'));
	avl.insert(ft::make_pair(21, 'c'));
	avl.insert(ft::make_pair(61, 'c'));
	avl.insert(ft::make_pair(8, 'c'));
	avl.insert(ft::make_pair(11, 'c'));
	avl.print();
	avl.erase(13);
	std::cout << "After deleting: " << std::endl;
	avl.print();

	return 0;
}

