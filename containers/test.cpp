#include <iostream>
#include <map>

using namespace std;

int main()
{
	map<int, float>::iterator it;
	cout << &(*it) << endl;
	cout << it->first << " " << it->second << endl;

	return 0;
}
