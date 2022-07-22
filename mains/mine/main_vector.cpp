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
	/////////////////////// TEST Vector ////////////////////

	std::cout << std::endl <<  CYAN <<  "************* Test Vector *************" << END_COLOR << std::endl << std::endl;


	std::cout << YELLOW << "Test 1: Default constructor" << END_COLOR << std::endl;
	vector<int> v4;
	if (v4.empty())
		std::cout << GREEN << "Default Constructor is empty! " << END_COLOR << std::endl;
	std::cout << std::endl;
	
	std::cout << YELLOW << "Test 2: Copy Constructor" << END_COLOR << std::endl;
	vector<int> vecto(8, 4);	
	vector<int> v3(vecto);	
	std::cout << "v3 (copy of v): ";
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl << "v3[1]: " << v3[1] << std::endl;
	std::cout << "v3.at(1): " << v3.at(1) << std::endl;
	std::cout << "Return an exception if the vector size is exceeded: " << std::endl;
	try {
		v3.at(2);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << YELLOW << "Test 3: Basic functions empty(), front(), back(), size()" << END_COLOR << std::endl;
	std::cout << "v: ";
	vector<int> v(3, 42);
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	
	std::cout << "* EMPTY *" << std::endl;
	if (!v.empty())
		std::cout << GREEN << "V is not empty!" << END_COLOR << std::endl << std::endl;
	vector<float> emp;
	std::cout << "Create an empty vector: " << emp.empty() << std::endl;
	std::cout << GREEN << "New vector is well empty!" << END_COLOR << std::endl << std::endl;

	
	std::cout << "* FRONT / BACK *" << std::endl;
	std::cout << "v.front() and v.back(): ";
	std::cout << v.front() << " " << v.back() << std::endl;

	std::cout << "v.front() != v.back(): " << (v.front() != v.back()) << std::endl;
	std::cout << GREEN << "Need to be true!" << END_COLOR << std::endl << std::endl;
	
	std::cout << "v.size(): ";
	if (!v.empty())
		std::cout << v.size() << std::endl;
	std::cout << std::endl;

	std::cout << YELLOW << "Test 4: begin(), end()" << END_COLOR << std::endl;
	vector<int> v2(2, 5);
	v = v2;
	std::cout << "Loop new vector(2, 5): ";
	for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	std::cout << "Loop copy of vector(2, 5): ";
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << YELLOW << "Test 5: " << END_COLOR << std::endl;
	const vector<int> vc(v3);
	std::cout << "Const vec: ";
	for (vector<int>::const_iterator it = vc.begin(); it != vc.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "Copy non const of vec" << std::endl << "and push_back() 4 new differents elements: " << std::endl;
	vector<int> vc5(vc);
	vc5.push_back(4);
	vc5.push_back(3);
	vc5.push_back(2);
	vc5.push_back(1);
	for (vector<int>::const_iterator it = vc5.begin(); it != vc5.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "vec.begin(): " << *vc5.begin() << std::endl;
	vector<int>::const_iterator last = vc5.end() - 1;
	std::cout << "vec.end() -1: " << *last << std::endl;
	std::cout << "vec.front(): " << vc5.front() << " vec.back(): " << vc5.back() << std::endl;
	std::cout << std::endl;
	std::cout << "vec[1]" << vc5[1] << std::endl;
	std::cout << "vec.at(1)" << vc5.at(1) << std::endl;
	std::cout << std::endl;
	std::cout << "Return an exception if the vector size is exceeded: " << std::endl;
	try {
		vc5.at(-3);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}


	std::cout << std::endl;

	std::cout << YELLOW << "Test 6: max_size(), size(), resize(), capacity(), reserve() " << END_COLOR << std::endl;
	vector<std::string> vect(1, "ok");
	vect.push_back("a");
	vect.push_back("b");
	vect.push_back("c");
	std::cout << "New vector: ";
	for (vector<std::string>::const_iterator it = vect.begin(); it != vect.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "* MAX_SIZE *" << std::endl;
	std::cout << "vect.max_size(): " << (vect.max_size()) << std::endl;
	std::cout << "* SIZE / CAPACITY *" << std::endl;
	std::cout << "vect size():        " << vect.size() << "   capacity: " << vect.capacity() << std::endl;
	
	std::cout << "* RESIZE *" << std::endl;
	std::cout << "vect.resize(2, d):  ";
	vect.resize(2, "d");
	std::cout << vect.size() << "   capacity: " << vect.capacity() << std::endl;
	std::cout << "vect.resize(9, e):  ";
	vect.resize(9, "e");
	std::cout << vect.size() << "   capacity: " << vect.capacity() << std::endl;
	std::cout << "vect.resize(35, f): ";
	vect.resize(35, "f");
	std::cout << vect.size() << "  capacity: " << vect.capacity() << std::endl;
	
	std::cout << std::endl;
	std::cout << "vect.at(): " << vect.at(5) << std::endl;
	std::cout << "vect.back(): " << vect.back() << std::endl;
	std::cout << "vect.pop_back() last element: ";
	vect.pop_back();
	std::cout << std::endl;
	std::cout << "vect.size(): " << vect.size() << "    capacity: " << vect.capacity() << std::endl;
	std::cout << std::endl;

	std::cout << "* RESERVE *" << std::endl;
	std::cout << "Reserve 1000 in vect: ";
	vect.reserve(1000);
	std::cout << "     vect.size()" << GREEN << vect.size() << END_COLOR << "      capacity: " << GREEN << vect.capacity() << END_COLOR << std::endl;
	
	std::cout << "* PUSH_BACK *" << std::endl;
	std::cout << "Add at vect 1000 elements: ";
	for (int i = 0; i < 1000; i++)
		vect.push_back("l");
	std::cout << "vect.size()" << GREEN << vect.size() << END_COLOR;
	std::cout << "    capacity: " << GREEN << vect.capacity() << END_COLOR << std::endl;
	std::cout << "Reserve 5: ";
	vect.reserve(5);
	std::cout << "                vect.size()" << GREEN << vect.size() << END_COLOR;
	std::cout << "    capacity: " << GREEN << vect.capacity() << END_COLOR << std::endl;
	
	std::cout << "* POP_BACK *" << std::endl;
	std::cout << "Delete vect 100 elements: ";
	for (int i = 0; i < 100; i++)
		vect.pop_back();
	std::cout << " vect.size()" << GREEN << vect.size() << END_COLOR;
	std::cout << "     capacity: " << GREEN << vect.capacity() << END_COLOR << std::endl;
	
	std::cout << std::endl;
	std::cout << std::endl;
	
	std::cout << YELLOW << "Test 7: clear(), assign() " << END_COLOR << std::endl;
	std::cout << "* CLEAR *" << std::endl;
	std::cout << "Clear vect: ";
	vect.clear();
	std::cout << "vect.size(): " << GREEN << vect.size() << END_COLOR << "    capacity: " << vect.capacity() << std::endl;
	std::cout << std::endl;
	
	std::cout << "* ASSIGN *" << std::endl;
	std::cout << "Create three new vector:" << std::endl;
	std::cout << "one: is empty";
	vector<int> one;
	std::cout << std::endl;
	std::cout << "two: ";
	vector<int> two(2, 10);
	for (vector<int>::iterator it = two.begin(); it != two.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "three: ";
	vector<int> three(3, 5);
	for (vector<int>::iterator it = three.begin(); it != three.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "Assign values to one(5, 12): ";
	one.assign(5, 12);
	for (vector<int>::iterator it = one.begin(); it != one.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	
	std::cout << "Assign from array: " << std::endl;
	std::cout << "Create an array of int: ";
	int	tab[] = {1997, 27, 12};
	for (int i = 0; i < 3; i++)
		std::cout << tab[i] << " ";
	std::cout << std::endl;
	std::cout << "Assign two elements of tab to three: ";
	three.assign(tab, tab + 2);
	for (vector<int>::iterator it = three.begin(); it != three.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << YELLOW << "Test 8: insert(), erase() and swap()" << END_COLOR << std::endl;
	
	std::cout << "* INSERT *" << std::endl;
	std::cout << "Create a new myvector(3, 100)" << std::endl;
	vector<int> myvector (3,100);
	vector<int>::iterator itie;

	std::cout << "Create an iterator from myvector.begin()" << std::endl;
	itie = myvector.begin();
	std::cout << "Insert in myvector: it, 200" << std::endl;
	itie = myvector.insert ( itie , 200 );
	std::cout << "it: " << *itie << std::endl;

	std::cout << "Insert in myvector: it, 2, 300" << std::endl;
	myvector.insert (itie,2,300);

	itie = myvector.begin();

	std::cout << std::endl << "Create anothervector(2, 400)" << std::endl;
	vector<int> anothervector (2,400);
	std::cout << "Insert in myvector: it + 2, anothervector.begin(), anothervector.end()" << std::endl;
	myvector.insert (itie+2,anothervector.begin(),anothervector.end());

	std::cout << std::endl << "Create an array (501, 502, 503)" << std::endl;
	int myarray [] = { 501,502,503 };
	std::cout << "Insert in myvector: myvector.begin(), array, array + 3" << std::endl;
	myvector.insert (myvector.begin(), myarray, myarray+3);
	std::cout << std::endl << "myvector contains:" << GREEN;
    for (itie=myvector.begin(); itie<myvector.end(); itie++)
	    std::cout << ' ' << *itie;
	std::cout << END_COLOR << std::endl;
	std::cout << std::endl;

	std::cout << "* ERASE *" << std::endl;
	std::cout << "myvector.size(): " << myvector.size() << std::endl;
	std::cout << "Erase to myvector: it + 1" << std::endl;
	itie = myvector.begin();
	myvector.erase(itie + 1);
	std::cout << "myvector.size(): " << myvector.size() << std::endl;
	std::cout << "myvector contains:" << GREEN;
    for (vector<int>::iterator it = myvector.begin(); it < myvector.end(); it++)
	    std::cout << ' ' << *it;
	std::cout << END_COLOR << std::endl;
	std::cout << std::endl;

	std::cout << "* SWAP *" << std::endl;
    std::cout << "Another vector: ";
	for (vector<int>::iterator it = anothervector.begin(); it < anothervector.end(); it++)
	    std::cout << ' ' << *it;
	std::cout << std::endl;
    std::cout << "Myvector: ";
	for (vector<int>::iterator it = myvector.begin(); it < myvector.end(); it++)
	    std::cout << ' ' << *it;
	std::cout << std::endl;
    std::cout << "Swap another vector with myvector:";
	anothervector.swap(myvector);
    std::cout << "Another vector: " << GREEN;
	for (vector<int>::iterator it = anothervector.begin(); it < anothervector.end(); it++)
	    std::cout << ' ' << *it;
	std::cout << END_COLOR << std::endl;
    std::cout << "Myvector: " << GREEN;
	for (vector<int>::iterator it = myvector.begin(); it < myvector.end(); it++)
	    std::cout << ' ' << *it;
	std::cout << END_COLOR << std::endl;

	std::cout << std::endl;
	std::cout << YELLOW << "Test 9: iterator incrementation & decrementation" << END_COLOR << std::endl;
	v3.push_back(10);
	v3.push_back(11);
	v3.push_back(12);
	v3.push_back(13);
	v3.push_back(14);
    for(vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	        std::cout << *it << " ";
	vector<int>::iterator it3(v3.begin());
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Test -= and += with iterator" << std::endl;
	it3 += 2;
	std::cout << "Increment it += 2: "<< *it3 << std::endl;
	std::cout << "Increment it += 2: "<< *(it3 += 2) << std::endl;
	it3 -= 2;
	std::cout << "Decrement it-=2: " << *it3 << std::endl;
	std::cout << "Decrement it-=2: " << *(it3 -= 2) << std::endl;
	
	std::cout << std::endl;
	vector<int>::const_iterator it4(v3.begin());
	std::cout << "Test -= and += with const iterator" << std::endl;
	it4 += 2;
	std::cout << "Increment it += 2: "<< *it4 << std::endl;
	std::cout << "Increment it += 2: "<< *(it4 += 2) << std::endl;
	it4 -= 2;
	std::cout << "Decrement it-=2: " << *it4 << std::endl;
	std::cout << "Decrement it-=2: " << *(it4 -= 2) << std::endl;
	std::cout << std::endl;
	return 0;
}
