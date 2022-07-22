#include <iostream>
#include <string>

#ifdef MINE
	#include "../../containers/map.hpp"
#else
	#include <map>
#endif

using namespace NAMESPACE;

#define CYAN "\033[0;36m"
#define MAGENTA "\033[0;35m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define END_COLOR "\033[0m"
#define OK "  ✅"


int main()
{

					//////////////// TEST MAP ////////////////////

	std::cout << CYAN << "********************************************************" << END_COLOR << std::endl;
	std::cout << CYAN << "********************* Test Map *************************" << END_COLOR << std::endl;
	std::cout << CYAN << "********************************************************" << END_COLOR << std::endl << std::endl;


						/***********  TEST 1  *************/

	std::cout << YELLOW << "  * Test 1: Constructors *  " << END_COLOR << std::endl;
	std::cout << std::endl;

	std::cout << "Test default constructor : ";
	map<std::string, int> default_;
	default_["K0"] = 10;
	default_["ok"] = 15;
	std::cout << GREEN << "Default constructor works!" << END_COLOR << std::endl << std::endl;

	std::cout << "Test range constructor : " << std::endl;
	map<std::string, int> range(default_.find("ok"), default_.end());
	std::cout << "range map print: { ";
	for (map<std::string, int>::iterator it = default_.begin(); it != default_.end(); it++)
		std::cout << it->first << " " << it->second << "; ";
	std::cout << "}" << std::endl;
	std::cout << "trying to find ok in map: find!" << std::endl;
	std::cout << GREEN << "Range constructor works!" << END_COLOR << std::endl << std::endl;
	
	std::cout << "Test copy constructor : ";
	map<std::string, int> copy(default_);
	std::cout << GREEN << "Copy constructor works!" << END_COLOR << std::endl;
	std::cout << std::endl << CYAN << "********************************************************" << END_COLOR << std::endl;
	std::cout << std::endl;
	

						/***********  TEST 2  *************/

	std::cout << YELLOW << "  * Test 2: Element Access *  " << END_COLOR << std::endl;
	std::cout << std::endl;


	std::cout << "Test at() : " << std::endl;
	std::cout << "(Access specified element with bound checking)" << std::endl << std::endl;
	map<char, int> m;
	m['d'] = 4;
	m['c'] = 99;
	m['e'] = 88;
	m['d'] = 3;
	m['e'];
	std::cout << std::endl;
	std::cout << "--- Create a new map ---" << std::endl;
	std::cout << std::endl;
	std::cout << "-> map print: { ";
	for (map<char, int>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " " << it->second << "; ";
	std::cout << std::endl;
	
	std::cout << std::endl;
	std::cout << "Try to access a non-existant element 'z': ";
	try {
		m.at('z');
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << GREEN << "Return exception!" << END_COLOR << std::endl;
	std::cout << std::endl;
	
	std::cout << "Try to access a non-existant element 'z' in a new map copy: ";
	const map<char, int> mc(m);
	try {
		mc.at('z');
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << GREEN << "Return exception!" << END_COLOR << std::endl;
	std::cout << std::endl;
	
	std::cout << "Try to access 'c' in map: ";
	try {
		m.at('c');
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;
	std::cout << GREEN << "Doesn't Return exception because 'c' is in map!" << END_COLOR << std::endl;
	std::cout << std::endl;
	
	std::cout << "Test operator[] : " << std::endl;
	std::cout << "(access specified element)" << std::endl;
	std::cout << std::endl;
	std::cout << "Display element map['c']: " << m['c'] << std::endl;
	std::cout << GREEN << "Operator[] works!" << END_COLOR << std::endl;
	std::cout << std::endl << CYAN << "********************************************************" << END_COLOR << std::endl;
	std::cout << std::endl;

						/***********  TEST 3  *************/

	std::cout << YELLOW << "  * Test 3: Capacity *  " << END_COLOR << std::endl;
	std::cout << std::endl;

	std::cout << "Test empty : " << std::endl;
	std::cout << "(Checks whether the container is empty)" << std::endl;
	std::cout << std::endl;
	map<char, int> emp;
	std::cout << "Test if the empty map is empty(): " << emp.empty() << GREEN << " TRUE" << END_COLOR << std::endl;
	std::cout << "Test if the non empty map is empty(): " << m.empty() << GREEN << " FALSE" << END_COLOR << std::endl;
	std::cout << std::endl;

	std::cout << "Test size() : " << std::endl;
	std::cout << "(Return the number of elements)" << std::endl;
	std::cout << std::endl;
	std::cout << "Size of map: " << m.size() << std::endl;
	std::cout << "Size of the copy of map: " << mc.size() << OK << std::endl;
	std::cout << "Size of an empty map: " << emp.size() << "   " << OK << std::endl;
	std::cout << GREEN << "Right size!" << END_COLOR << std::endl;
	std::cout << std::endl;

	std::cout << "Test max_size() : " << std::endl;
	std::cout << "(Returns the maximum possible number of elements)" << std::endl;
	std::cout << std::endl;
	std::cout << "Max Size of map: " << m.max_size() << "            " << OK << std::endl;
	std::cout << "Max Size of the copy of map: " << mc.max_size() << OK << std::endl;
	std::cout << "Max Size of an empty map: " << emp.max_size() << "   " << OK << std::endl;
	std::cout << GREEN << "Max_size works! It can be different from that of the stl." << END_COLOR << std::endl;
	std::cout << std::endl << CYAN << "********************************************************" << END_COLOR << std::endl;
	std::cout << std::endl;
	
	
						/***********  TEST 4  *************/

	std::cout << YELLOW << "  * Test 4: Modifiers *  " << END_COLOR << std::endl;
	std::cout << std::endl;

	std::cout << "Test clear : " << std::endl;
	std::cout << "(Erase all elements from the container)" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Size of map before clear(): " << m.size() << OK << std::endl;
	m.clear();
	std::cout << "Size of map after clear(): " << m.size() << " " << OK << std::endl;
	std::cout << GREEN << "Clear works correctly!" << END_COLOR << std::endl;
	std::cout << std::endl;

	std::cout << "Test insert : " << std::endl;
	std::cout << "(Insert elements from the container)" << std::endl;
	std::cout << std::endl;

	std::cout << "Insert 3 elements in map: " << std::endl;
	m.insert(make_pair('p', 75));
	m.insert(make_pair('q', 715));
	m.insert(make_pair('r', 7));
	std::cout << "map print after insertion: { ";
	for (map<char, int>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " " << it->second << "; ";
	std::cout << "}" << std::endl;
	std::cout << GREEN << "All the elements have been well inserted!" << END_COLOR << std::endl;
	std::cout << std::endl;
	
	std::cout << "Test erase : " << std::endl;
	std::cout << "(Erases elements)" << std::endl;
	std::cout << std::endl;

	std::cout << "Erase 2 elements in map: " << std::endl;
	std::cout << MAGENTA << "Before: " << END_COLOR << std::endl;
	std::cout << "map print: { ";
	for (map<char, int>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " " << it->second << "; ";
	std::cout << "}" << std::endl;
	std::cout << "Size: " << m.size() << std::endl << std::endl;

	std::cout << MAGENTA << "After: " << END_COLOR << std::endl;
	m.erase('p');
	m.erase('q');
	std::cout << "map print: { ";
	for (map<char, int>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " " << it->second << "; ";
	std::cout << "}" << std::endl;
	std::cout << "Size: " << m.size() << std::endl;
	std::cout << GREEN << "The two elements have been well erased!" << END_COLOR << std::endl;
	std::cout << std::endl;
	
	std::cout << "Test swap : " << std::endl;
	std::cout << "(Swap the contents)" << std::endl;
	std::cout << std::endl;

	map<char, int> sw1, sw2;
	sw1['q'] = 42;
	sw1['r'] = 55;
	sw1['d'] = 25;
	sw1['o'] = 10;
	sw1['w'] = 90;
	sw1['q'] = 142;

	sw2['r'] = 455;
	sw2['d'] = 225;
	sw2['o'] = 100;
	sw2['w'] = 4;
	
	std::cout << MAGENTA << "Before: " << END_COLOR << std::endl;
	std::cout << "First map print: { ";
	for (map<char, int>::iterator it = sw1.begin(); it != sw1.end(); it++)
		std::cout << it->first << " " << it->second << "; ";
	std::cout << "}" << std::endl;
	std::cout << "Second map print: { ";
	for (map<char, int>::iterator it = sw2.begin(); it != sw2.end(); it++)
		std::cout << it->first << " " << it->second << "; ";
	std::cout << "}" << std::endl << std::endl;

	sw1.swap(sw2);
	
	std::cout << MAGENTA << "After: " << END_COLOR << std::endl;
	std::cout << "First map print: { ";
	for (map<char, int>::iterator it = sw1.begin(); it != sw1.end(); it++)
		std::cout << it->first << " " << it->second << "; ";
	std::cout << "}" << std::endl;
	std::cout << "Second map print: { ";
	for (map<char, int>::iterator it = sw2.begin(); it != sw2.end(); it++)
		std::cout << it->first << " " << it->second << "; ";
	std::cout << "}" << std::endl;
	std::cout << GREEN << "swap() !" << OK << END_COLOR << std::endl;
	std::cout << std::endl << CYAN << "********************************************************" << END_COLOR << std::endl;
	std::cout << std::endl;

	
						/***********  TEST 5  *************/
	std::cout << YELLOW << "  * Test 5: Lookup *  " << END_COLOR << std::endl;
	std::cout << std::endl;

	std::cout << "Test lower_bound() : " << std::endl;
	std::cout << "(returns an iterator to the first element not less than the given key)" << std::endl;
	std::cout << std::endl;
	
	map<char, int>::const_iterator cit = mc.find('c');
	std::cout << "Map print: { ";
	for (map<char, int>::const_iterator it = mc.begin(); it != mc.end(); it++)
		std::cout << it->first << " " << it->second << "; ";
	std::cout << "}" << std::endl;
	std::cout << "Try to lower_bound('e') : ";
	std::cout << std::endl;
	std::cout << cit->first << " " << cit->second << std::endl;
	cit = mc.lower_bound('e');
	std::cout << cit->first << " " << cit->second << std::endl;
	std::cout << GREEN << "Lower_bound is okay!" << OK << END_COLOR << std::endl;
	std::cout << std::endl;
	
	std::cout << "Test upper_bound() : " << std::endl;
	std::cout << "(returns an iterator to the first element greater than the given key)" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Map print: { ";
	for (map<char, int>::const_iterator it = mc.begin(); it != mc.end(); it++)
		std::cout << it->first << " " << it->second << "; ";
	std::cout << "}" << std::endl;
	std::cout << "Try to upper_bound('d') : ";
	std::cout << std::endl;
	std::cout << cit->first << " " << cit->second << std::endl;
	cit = mc.upper_bound('d');
	std::cout << cit->first << " " << cit->second << std::endl;
	std::cout << std::endl;
	std::cout << "Try to upper_bound('c') : ";
	std::cout << std::endl;
	std::cout << cit->first << " " << cit->second << std::endl;
	cit = mc.upper_bound('c');
	std::cout << cit->first << " " << cit->second << std::endl;
	std::cout << GREEN << "upper_bound is okay!" << OK << END_COLOR << std::endl;
	std::cout << std::endl;
	

	std::cout << "Test equal_range() : " << std::endl;
	std::cout << "(returns range of elements matcing a specific keys)" << std::endl;
	std::cout << std::endl;
	
	pair<map<char, int>::const_iterator, map<char, int>::const_iterator> pc;
	pc = mc.equal_range('d');
	std::cout << "equal range: ";
	std::cout << pc.first->first << " " << pc.first->second << ", ";
	std::cout << pc.second->first << " " << pc.second->second << std::endl;
	std::cout << GREEN << "equal_range is okay!" << OK << END_COLOR << std::endl;
	std::cout << std::endl;

	std::cout << std::endl << CYAN << "********************************************************" << END_COLOR << std::endl;
	std::cout << std::endl;
	

						/***********  TEST 6  *************/
	std::cout << YELLOW << "  * Test 6: Other tests *  " << END_COLOR << std::endl;
	std::cout << std::endl;
	
	m['q'] = 42;
	m['r'] = 55;
	m['d'] = 25;
	m['o'] = 10;
	m['w'] = 90;

	std::cout << std::boolalpha;
	pair<map<char, int>::iterator, bool> ret = m.insert(make_pair('h', 216));
	std::cout << "insert ret: " << ret.first->first << " " << ret.first->second << ", " << ret.second << std::endl;
	ret = m.insert(make_pair('h', 212));
	std::cout << "insert ret: " << ret.first->first << " " << ret.first->second << ", " << ret.second << std::endl;
	std::cout << std::endl;

	map<char, int>::iterator ret2 = m.insert(m.begin(), make_pair('w', 99));
	std::cout << "2nd insert ret: ";
	std::cout << ret2->first << " " << ret2->second << std::endl;
	std::cout << std::endl;
	
	map<char, int> m2(m);
	ret2 = m.insert(m2.begin(), make_pair('w', 99));
	std::cout << "2nd insert ret: ";
	std::cout << ret2->first << " " << ret2->second << std::endl;

	std::cout << "Print map: ";
	for (map<char, int>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " " << it->second;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Print second map: ";
	for (map<char, int>::const_iterator it = mc.begin(); it != mc.end(); it++)
		std::cout << it->first << " " << it->second;
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Template tests" << std::endl;
	map<char, int> mt(m.begin(), m.end());
	mt.insert(mt.begin(), mt.end());
	for (map<char, int>::iterator it = mt.begin(); it != mt.end(); it++)
		std::cout << it->first << " " << it->second << ", ";
	std::cout << std::endl;
	

	std::cout << std::endl << CYAN << "********************************************************" << END_COLOR << std::endl;
	std::cout << std::endl;

	return 0;
}
