#include "vector/vector.hpp"
#include <iostream>
#include <vector>

using namespace NAMESPACE;

int main()
{
	vector<int> v(3, 42);

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << std::endl;
	return (0);
}
