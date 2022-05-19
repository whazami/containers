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
	std::cout << v.size() << " " << v.capacity() << std::endl;
	
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
	std::cout << v3.size() << " " << v3.capacity() << std::endl;
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
	std::cout << v4.size() << " " << v4.capacity() << std::endl;

	const vector<int> vc(v3);
	std::cout << vc.size() << " " << vc.capacity() << std::endl;
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
	v5[5] = 66.6f;
	std::cout << "CAPA V5 " << v5.capacity() << std::endl;
	v5.assign(3, 33.3f);
	std::cout << "Testing assign..." << std::endl;
	for (vector<float>::iterator it = v5.begin(); it != v5.end(); it++)
		std::cout << *it << " ";
	std::cout << *v5.end() << " ";
	std::cout << v5[4] << " " << v5[5] << " " << v5.back() << std::endl;
	v5.assign(v3.begin(), v3.end());
	std::cout << v5.size() << " " << v5.capacity() << std::endl;
	for (int i = 0; i < 20; i++) {
		v5.push_back(42.42f);
		std::cout << v5.size() << " " << v5.capacity() << std::endl;
	}
	for (vector<float>::iterator it = v5.begin(); it != v5.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	/// ** SUPER VOID VECTOR TESTER ** ////
	// Should not segfault
	vector< vector<float> > vvs(10);
	vvs[0].push_back(4.5f);
	std::cout << vvs[0].back() << " " << vvs[0].front() << std::endl;
	vvs[1] = v5;
	std::cout << vvs[1].front() << std::endl;
	try {
		(void)vvs[2].at(0);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << vvs[3].size() << " " << vvs[3].capacity() << std::endl;
	vvs[3].assign(v5.begin(), v5.end());
	std::cout << vvs[3].size() << " " << vvs[3].capacity() << std::endl;
	std::cout << vvs[3][0] << vvs[3][1] << std::endl;
	vvs[4].assign(4, 4.44f);
	for (vector<float>::iterator it = vvs[4].begin(); it != vvs[4].end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	// Should segfault
	vector<float> vv;
	//vector<float>::iterator it = vv.begin(); std::cout << *it;
	//vector<float>::iterator it = vv.end(); std::cout << *it;
	//std::cout << vv[0];
	//std::cout << vv.front();
	//std::cout << vv.back();
	// pop_back


	vector<float> v6(3, 5.5f);
	v6.pop_back();
	std::cout << v6.size() << " " << v6.capacity() << std::endl;
	v6.reserve(5);
	std::cout << v6.size() << " " << v6.capacity() << std::endl;
	for (vector<float>::iterator it = v6.begin(); it != v6.end(); it++)
		std::cout << *it << std::endl;
	try {
		v6.reserve(2305843009213693952); // length_error exception
		std::cout << "vector max size: " << v6.max_size() << std::endl;
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		v6.reserve(2305843009213693950); // bad_alloc exception
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	// Range constructor
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
