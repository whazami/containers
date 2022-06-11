#include "AVL.hpp"
#include <iostream>

template <typename T>
bool insert(T *avl, int key) {
	static char c = 'a';
	return avl->insert(ft::make_pair(key, c++));
}

template <typename T>
void printAvlInOrder(T* root, T* end) {
	T* p = root;
	if (!root)
		return;
	while (p->left)
		p = p->left;
	for(;p != end; p = p->next())
		std::cout << p->pair.first << " " << p->pair.second << (p->next() ? ", " : "");
	std::cout << std::endl;
}

int main()
{
	typedef std::less<int> key_compare;
	typedef std::allocator<ft::pair<const int, char> > allocator_type;
	key_compare comp;
	allocator_type alloc;
	ft::AVL<int, char, key_compare, allocator_type> avl(comp, alloc);

	std::cout << std::boolalpha;
	insert(&avl, 33);
	insert(&avl, 13);
	insert(&avl, 53);
	insert(&avl, 19);
	insert(&avl, 21);
	insert(&avl, 44);
	insert(&avl, 61);
	insert(&avl, 8);
	std::cout << "should be true: " << insert(&avl, 11) << std::endl;
	std::cout << "should be false: " << avl.insert(ft::make_pair(44, 'z')) << std::endl;
	avl.print();
	printAvlInOrder(avl.getRoot(), avl.end());
	avl.erase(19);
	std::cout << "After deleting 19: " << std::endl;
	avl.print();
	printAvlInOrder(avl.getRoot(), avl.end());
	avl.erase(44);
	std::cout << "After deleting 44: " << std::endl;
	avl.print();
	printAvlInOrder(avl.getRoot(), avl.end());
	avl.erase(11);
	std::cout << "After deleting 11: " << std::endl;
	avl.print();
	printAvlInOrder(avl.getRoot(), avl.end());
	avl.erase(33);
	std::cout << "After deleting 33: " << std::endl;
	avl.print();
	printAvlInOrder(avl.getRoot(), avl.end());
	avl.erase(13);
	std::cout << "After deleting 13: " << std::endl;
	avl.print();
	printAvlInOrder(avl.getRoot(), avl.end());
	avl.erase(61);
	std::cout << "After deleting 61: " << std::endl;
	avl.print();
	printAvlInOrder(avl.getRoot(), avl.end());
	avl.erase(21);
	std::cout << "After deleting 21: " << std::endl;
	avl.print();
	printAvlInOrder(avl.getRoot(), avl.end());
	avl.erase(8);
	std::cout << "After deleting 8: " << std::endl;
	avl.print();
	printAvlInOrder(avl.getRoot(), avl.end());
	std::cout << "should be true: " << avl.erase(53) << std::endl;
	std::cout << "should be false: " << avl.erase(53) << std::endl;
	std::cout << "After deleting 53: " << std::endl;
	avl.print();
	printAvlInOrder(avl.getRoot(), avl.end());

	return 0;
}

