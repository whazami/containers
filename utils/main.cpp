#include "is_integral.hpp"
#include <iostream>

int main()
{
	std::cout << ft::is_integral<int>::value << std::endl;
	std::cout << ft::is_integral<std::string>::value << std::endl;
	std::cout << ft::is_integral<char>::value << std::endl;
	return 0;
}
