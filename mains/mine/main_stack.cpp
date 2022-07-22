#include <iostream>
#include <unistd.h>

#ifdef MINE
	#include "../../containers/vector.hpp"
	#include "../../containers/stack.hpp"
#else
	#include <vector>
	#include <stack>
#endif

using namespace NAMESPACE;

#define CYAN "\033[0;36m"
#define END_COLOR "\033[0m"
#define MAGENTA "\033[0;35m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"


int main()
{
	////////////////////// TEST STACK //////////////////////////////

	std::cout << std::endl << CYAN << "************ Test Stack ************" << END_COLOR << std::endl << std::endl;

		
	std::cout << YELLOW << "  * Test 1: Constructor of stack Test *  " << END_COLOR << std::endl;
	vector<int> myvec(3, 10);
	stack<int> first; 				    // empty stack
	std::cout << "size of empty stack: " << first.size() << std::endl;
	if (first.empty())
		std::cout << "test empty(), first is empty" << std::endl << std::endl;
	
	stack<int, vector<int> > second (myvec);		// stack initialized to copy of vector 
	std::cout << "size of stack copy of vector: " << second.size() << std::endl;
	if (!second.empty())
		std::cout << "test empty(), second is not empty" << std::endl << std::endl;
	std::cout << "test top(): " << second.top() << std::endl;	

	stack<int> c1;
	c1.push(5);
	std::cout << "Stack c1 size: " << c1.size() << std::endl;
	stack<int> c2(c1);
	std::cout << "Copy stack c1 in c2 size: " << c2.size() << std::endl;
	c2.push(6);
	c2.push(3);
	c2.push(2);
	std::cout << "Stack c2 size after push: " << c2.size() << std::endl;
	std::cout << GREEN << "Everything works!" << END_COLOR << std::endl;

	std::cout << std::endl;
	

	std::cout << YELLOW << "  * Test 2: top *  " << END_COLOR << std::endl;
	//std::cout << "c1 top: " << c1.top() << std::endl; //Need to segfault
	std::cout << "top(): " << second.top() << std::endl;
	std::cout << GREEN << "Display the element at the top in the stack!" << END_COLOR << std::endl;
	std::cout << std::endl;

	std::cout << YELLOW << "  * Test 3: push() *  " << END_COLOR << std::endl;
	stack<int> mystack;
	std::cout << "size of mystack: " << mystack.size() << std::endl;
	for (int i = 0; i < 5; i++)
	{
		mystack.push(i);
		std::cout << "i: " << i  << std::endl;
		std::cout << "top(): " << mystack.top() << std::endl;
	}
	std::cout << "size of mystack: " << mystack.size() << std::endl;
	std::cout << GREEN << "Push() works correctly!" << END_COLOR << std::endl;
	std::cout << std::endl;

	std::cout << YELLOW << "  * Test 4: pop() *  " << END_COLOR << std::endl;
	std::cout << "size of mystack: " << mystack.size() << std::endl;
	std::cout << "mystack display top() and next pop this one: ";
	for (int i = 0; i < 5; i++)
	{
		std::cout << mystack.top() << " ";
		mystack.pop();
	}
	std::cout << std::endl;
	std::cout << "size of mystack: " << mystack.size() << std::endl;
	std::cout << GREEN << "pop() removed all the element of the stack!" << END_COLOR << std::endl;
	std::cout << std::endl;

	std::cout << YELLOW << "  * Test 5: Non member relational operators *  " << END_COLOR << std::endl;
	stack<float> lhs;
	lhs.push(12);
	lhs.push(13);
	lhs.push(14);
	lhs.push(15);
	stack<float> rhs(lhs);
	std::cout << "lhs and rhs are equal:" << std::endl;
	std::cout << "Compare lhs == rhs: ";
	std::cout << ((lhs == rhs) ? GREEN : MAGENTA) << ((lhs == rhs) ? "valid true " : "invalid false ") << END_COLOR << (lhs == rhs) << std::endl;
	std::cout << "Compare lhs != rhs: ";
	std::cout << ((lhs != rhs) ? MAGENTA : GREEN) << ((lhs != rhs) ? "invalid true " : "valid false ") << END_COLOR << (lhs != rhs) << std::endl;
	std::cout << "Compare lhs < rhs: ";
	std::cout << ((lhs < rhs) ? MAGENTA : GREEN) << ((lhs < rhs) ? "invalid true " : "valid false ") << END_COLOR << (lhs < rhs) << std::endl;
	std::cout << "Compare lhs > rhs: ";
	std::cout << ((lhs > rhs) ? MAGENTA : GREEN) << ((lhs > rhs) ? "invalid true " : "valid false ") << END_COLOR << (lhs > rhs) << std::endl;
	std::cout << "Compare lhs <= rhs: ";
	std::cout << ((lhs <= rhs) ? GREEN : MAGENTA) << ((lhs <= rhs) ? "valid true " : "invalid false ") << END_COLOR << (lhs <= rhs) << std::endl;
	std::cout << "Compare lhs >= rhs: ";
	std::cout << ((lhs >= rhs) ? GREEN : MAGENTA) << ((lhs >= rhs) ? "valid true " : "invalid false ") << END_COLOR << (lhs >= rhs) << std::endl;
	
	rhs.push(112);
	rhs.push(1);
	std::cout << std::endl << "lhs and rhs are not equal and rhs > to lhs:" << std::endl;
	std::cout << "Compare lhs == rhs: ";
	std::cout << ((lhs == rhs) ? MAGENTA : GREEN) << ((lhs == rhs) ? "invalid true " : "valid false ") << END_COLOR << (lhs == rhs) << std::endl;
	std::cout << "Compare lhs != rhs: ";
	std::cout << ((lhs != rhs) ? GREEN : MAGENTA) << ((lhs != rhs) ? "valid true " : "invalid false ") << END_COLOR << (lhs != rhs) << std::endl;
	std::cout << "Compare lhs < rhs: ";
	std::cout << ((lhs < rhs) ? GREEN : MAGENTA) << ((lhs < rhs) ? "valid true " : "invalid false ") << END_COLOR << (lhs < rhs) << std::endl;
	std::cout << "Compare lhs > rhs: ";
	std::cout << ((lhs > rhs) ? MAGENTA : GREEN) << ((lhs > rhs) ? "invalid true " : "valid false ") << END_COLOR << (lhs > rhs) << std::endl;
	std::cout << "Compare lhs <= rhs: ";
	std::cout << ((lhs <= rhs) ? GREEN : MAGENTA) << ((lhs <= rhs) ? "valid true " : "invalid false ") << END_COLOR << (lhs <= rhs) << std::endl;
	std::cout << "Compare lhs >= rhs: ";
	std::cout << ((lhs >= rhs) ? MAGENTA : GREEN) << ((lhs >= rhs) ? "invalid true " : "valid false ") << END_COLOR << (lhs >= rhs) << std::endl;
	std::cout << GREEN << "Every relationnal operators works!" << END_COLOR << std::endl;

	return 0;
}
