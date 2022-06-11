#include <iostream>
#include <string>

#ifdef MINE
	#include "../../../containers/map.hpp"
#else
	#include <map>
#endif

using namespace NAMESPACE;

int main()
{
	map<char, int> m;
	m['d'] = 4;
	m['c'] = 99;
	m['e'] = 88;
	m['d'] = 3;
	m['e'];

	try {
		m.at('z');
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	const map<char, int> mc(m);
	try {
		mc.at('z');
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	map<char, int>::const_iterator cit = mc.find('c');
	std::cout << cit->first << " " << cit->second << std::endl;
	cit = mc.lower_bound('e');
	std::cout << cit->first << " " << cit->second << std::endl;
	pair<map<char, int>::const_iterator, map<char, int>::const_iterator> pc;
	pc = mc.equal_range('d');
	std::cout << "equal range: ";
	std::cout << pc.first->first << " " << pc.first->second << ", ";
	std::cout << pc.second->first << " " << pc.second->second << std::endl;

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

	map<char, int>::iterator ret2 = m.insert(m.begin(), make_pair('w', 99));
	std::cout << "2nd insert ret: ";
	std::cout << ret2->first << " " << ret2->second << std::endl;
	map<char, int> m2(m);
	ret2 = m.insert(m2.begin(), make_pair('w', 99));
	std::cout << "2nd insert ret: ";
	std::cout << ret2->first << " " << ret2->second << std::endl;
	// Should segfault
	/*map<char, int>::iterator nil;
	ret2 = m.insert(nil, make_pair('w', 99));
	std::cout << "2nd insert ret: ";
	std::cout << ret2->first << " " << ret2->second << std::endl;*/

	for (map<char, int>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	std::cout << std::endl;
	for (map<char, int>::const_iterator it = mc.begin(); it != mc.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;

	std::cout << "m size: " << m.size() << std::endl;
	std::cout << "mc size: " << mc.size() << std::endl;

	std::cout << "Template tests" << std::endl;
	map<char, int> mt(m.begin(), m.end());
	mt.insert(mt.begin(), mt.end());
	for (map<char, int>::iterator it = mt.begin(); it != mt.end(); it++)
		std::cout << it->first << " " << it->second << ", ";
	std::cout << std::endl;
	return 0;
}
