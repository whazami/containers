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

	for (map<char, int>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;

	try {
		m.at('z');
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	/*const map<char, int> mc(m);
	try {
		mc.at('z');
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}*/
	return 0;
}
