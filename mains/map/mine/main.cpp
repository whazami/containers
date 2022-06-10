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

	m['q'] = 42;
	m['r'] = 55;
	m['d'] = 25;
	m['o'] = 10;
	m['w'] = 90;

	for (map<char, int>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	std::cout << std::endl;
	for (map<char, int>::const_iterator it = mc.begin(); it != mc.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	return 0;
}
