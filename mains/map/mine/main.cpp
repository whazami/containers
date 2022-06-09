#include <iostream>

#ifdef MINE
	#include "../../../containers/map.hpp"
#else
	#include <map>
#endif

using namespace NAMESPACE;

int main()
{
	map<char, int> m;
	(void)m;

	return 0;
}
