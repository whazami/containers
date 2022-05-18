#include <iostream>

#ifdef MINE
	#include "vector/vector.hpp"
#else
	#include <vector>
#endif

using namespace NAMESPACE;

int main()
{
	vector<int> v(3, 42);

	std::cout << "v: ";
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	if (v.empty())
		std::cout << "hey" << std::endl;

	std::cout << "v.front() and v.back(): ";
	std::cout << v.front() << " " << v.back() << std::endl;
	
	std::cout << "v.size(): ";
	if (!v.empty())
		std::cout << v.size() << std::endl;
	
	vector<int> v2(2, 5);
	v = v2;
	std::cout << "v2: ";
	for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	std::cout << "v: ";
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	vector<int> v3(v);	
	std::cout << "v3 (copy of v): ";
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl << "v3[1]: " << v3[1] << std::endl;
	std::cout << v3.at(1) << std::endl;
	try {
		v3.at(2);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	vector<int> v4;
	if (v4.empty())
		std::cout << "Default Constructor is empty " << std::endl;

	const vector<int> vc(v3);
	std::cout << *vc.begin() << std::endl;
	vector<int>::const_iterator last = vc.end() - 1;
	std::cout << *last << std::endl;
	std::cout << vc.front() << " " << vc.back() << std::endl;
	std::cout << vc[1] << std::endl;
	std::cout << vc.at(1) << std::endl;
	try {
		vc.at(-3);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	vector<float> v5(7, 77.7f);
	v5.assign(6, 66.6f);
	std::cout << "Testing assign..." << std::endl;
	for (vector<float>::iterator it = v5.begin(); it != v5.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	v5.assign(v3.begin(), v3.end());
	for (int i = 0; i < 20; i++)
		v5.push_back(42.42f);
	for (vector<float>::iterator it = v5.begin(); it != v5.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	/// ** SUPER VOID VECTOR TESTER ** ////
	vector< vector<float> > vvs(1);
	//v4.assign
	/*v4.push_back(1);
	std::cout << v4.back() << std::endl;*/ 

	/*vector<float> v0(v3.begin(), v3.end());
	std::cout << "v0 Range constructor: ";
	for (vector<float>::iterator it = v0.begin(); it != v0.end(); it++)
	std::cout << *it << " ";
	std::cout << std::endl;*/
	return (0);
}

// apres avoir fini ce main, tu peux faire l'operator= et le constructeur de copie
// (qui sont codes par defaut par le c++, donc n'hesite pas a ajouter des cout dedans
// pour verifier qu'il vient bien dans le tien)
