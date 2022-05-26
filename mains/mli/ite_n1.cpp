#include <iostream>
#include <string>

#ifdef MINE
	#include "../../vector/vector.hpp"
#else
	#include <vector>
#endif

using namespace NAMESPACE;

#define TESTED_TYPE std::string

void printSize(vector<TESTED_TYPE> v) {
	std::cout << v.size() << " " << v.capacity() << std::endl;
}

void	checkErase(vector<TESTED_TYPE> const &vct,
					vector<TESTED_TYPE>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	printSize(vct);
}

int		main(void)
{
	const int size = 5;
	vector<TESTED_TYPE> const vct(size);
	vector<TESTED_TYPE>::iterator it = vct.begin(); // <-- error expected

	for (int i = 0; i < size; ++i)
		it[i] = i;

	return (0);
}
