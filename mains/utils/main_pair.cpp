#include <iostream>
#include <string>

#ifdef MINE
	#include "../../utils/pair.hpp"
#else
	#include <utility>
#endif

using namespace NAMESPACE;

template <class T1, class T2, class T3, class T4>
void compare(const pair<T1, T2>& p, const pair<T3, T4>& p2)
{
	std::cout << std::boolalpha;
	std::cout << (p == p2) << std::endl;
	std::cout << (p != p2) << std::endl;
	std::cout << (p < p2) << std::endl;
	std::cout << (p <= p2) << std::endl;
	std::cout << (p > p2) << std::endl;
	std::cout << (p >= p2) << std::endl;
}

int main()
{
	std::cout << "### Pair Tester ###" << std::endl;
	pair<int, float> p;
	pair<char, double> p2('c', 5.6);
	pair<int, float> p3(p);
	pair<int, float> p4(p2);
	pair<int, float> p5 = p4;

	std::cout << "p: " << p.first << " " << p.second << std::endl;
	std::cout << "p2: " << p2.first << " " << p2.second << std::endl;
	std::cout << "p3: " << p3.first << " " << p3.second << std::endl;
	std::cout << "p4: " << p4.first << " " << p4.second << std::endl;
	std::cout << "p5: " << p5.first << " " << p5.second << std::endl;

	compare(p, p);
	compare(p, p3);
	compare(p, p4);
	compare(p, p5);
	compare(p3, p3);
	compare(p3, p4);
	compare(p3, p5);
	compare(p4, p4);
	compare(p4, p5);
	compare(p5, p5);

	std::cout << "### make_pair Tester ###" << std::endl;
	pair <int,int> foo;
	pair <int,int> bar;

	foo = make_pair (10,20);
	bar = make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

	std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
	std::cout << "bar: " << bar.first << ", " << bar.second << '\n';

	// Should not compile
	/*pair<std::string, char> p6(p5);

	std::cout << "p6: " << p6.first << " " << p6.second << std::endl;
	compare(p2, p3);
	pair<int, float> p7 = make_pair("hey", 42.f);
	(void)p7;*/

	return 0;
}
