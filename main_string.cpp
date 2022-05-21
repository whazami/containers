#include <iostream>
#include <string>

#ifdef MINE
	#include "vector/vector.hpp"
#else
	#include <vector>
#endif

using namespace NAMESPACE;

void print_capacity(vector<std::string> v)
{
	std::cout << v.size() << " " << v.capacity() << std::endl;
}

void resize_test(vector<std::string> v)
{
    std::cout << v.capacity() << std::endl;
	v.resize(6);
	std::cout << v.capacity() << std::endl;
	v.resize(0);
	std::cout << v.capacity() << std::endl;
	v.resize(9, "resize 9");
	std::cout << v.capacity() << std::endl;
	v.resize(13);
	std::cout << v.capacity() << std::endl;
	v.resize(27);
	std::cout << v.capacity() << std::endl;
											    
	for (vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int main()
{
	vector<std::string> v(3, "42");
	std::cout << v.size() << " " << v.capacity() << std::endl;
	
	std::cout << "v: ";
	for (vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	if (v.empty())
		std::cout << "hey" << std::endl;

	std::cout << "v.front() and v.back(): ";
	std::cout << v.front() << " " << v.back() << std::endl;
	
	std::cout << "v.size(): ";
	if (!v.empty())
		std::cout << v.size() << std::endl;
	
	vector<std::string> v2(2, "5");
	v = v2;
	std::cout << "v2: ";
	for (vector<std::string>::iterator it = v2.begin(); it != v2.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	std::cout << "v: ";
	for (vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	vector<std::string> v3(v);
	std::cout << v3.size() << " " << v3.capacity() << std::endl;
	std::cout << "v3 (copy of v): ";
	for (vector<std::string>::iterator it = v3.begin(); it != v3.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl << "v3[1]: " << v3[1] << std::endl;
	std::cout << v3.at(1) << std::endl;
	try {
		v3.at(2);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	vector<std::string> v4;
	if (v4.empty())
		std::cout << "Default Constructor is empty " << std::endl;
	std::cout << v4.size() << " " << v4.capacity() << std::endl;

	const vector<std::string> vc(v3);
	std::cout << vc.size() << " " << vc.capacity() << std::endl;
	std::cout << *vc.begin() << std::endl;
	vector<std::string>::const_iterator last = vc.end() - 1;
	std::cout << *last << std::endl;
	std::cout << vc.front() << " " << vc.back() << std::endl;
	std::cout << vc[1] << std::endl;
	std::cout << vc.at(1) << std::endl;
	try {
		vc.at(-3);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	vector<std::string> v5(7, "77.7f");
	v5[5] = "66.6f";
	std::cout << "CAPA V5 " << v5.capacity() << std::endl;
	v5.assign(3, "33.3f");
	std::cout << "Testing assign..." << std::endl;
	for (vector<std::string>::iterator it = v5.begin(); it != v5.end(); it++)
		std::cout << *it << " ";
	std::cout << *v5.end() << " ";
	std::cout << v5[4] << " " << v5[5] << " " << v5.back() << std::endl;
	v5.assign(v3.begin(), v3.end());
	std::cout << v5.size() << " " << v5.capacity() << std::endl;
	for (int i = 0; i < 20; i++) {
		v5.push_back("42.42f");
		std::cout << v5.size() << " " << v5.capacity() << std::endl;
	}
	for (vector<std::string>::iterator it = v5.begin(); it != v5.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	/// ** SUPER VOID VECTOR TESTER ** ////
	// Should not segfault
	vector< vector<std::string> > vvs(10);
	vvs[0].push_back("4.5f");
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
	vvs[4].assign(4, "4.44f");
	for (vector<std::string>::iterator it = vvs[4].begin(); it != vvs[4].end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	vvs[5].reserve(7);
	std::cout << vvs[5].size() << " " << vvs[5].capacity() << std::endl;
	vvs[6].resize(5, "100");
	std::cout << vvs[6].size() << " " << vvs[6].capacity() << std::endl;
	for (vector<std::string>::iterator it = vvs[6].begin(); it != vvs[6].end(); it++)
		std::cout << *it << std::endl;
	std::cout << "yooyoo test" << std::endl;
	vvs[7].insert(vvs[7].begin(), "9");
	std::cout << vvs[7].front() << std::endl;
	vvs[8].insert(vvs[8].begin(), 5, "21.f");
	std::cout << vvs[8].size() << " " << vvs[8].capacity() << std::endl;
	for (vector<std::string>::iterator it = vvs[8].begin(); it != vvs[8].end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	// Should segfault
	vector<std::string> vv;
	//vector<std::string>::iterator it = vv.begin(); std::cout << *it;
	//vector<std::string>::iterator it = vv.end(); std::cout << *it;
	//std::cout << vv[0];
	//std::cout << vv.front();
	//std::cout << vv.back();
	// pop_back


	vector<std::string> v6(3, "5.5f");
	v6.pop_back();
	std::cout << v6.size() << " " << v6.capacity() << std::endl;
	v6.reserve(5);
	std::cout << v6.size() << " " << v6.capacity() << std::endl;
	for (vector<std::string>::iterator it = v6.begin(); it != v6.end(); it++)
		std::cout << *it << std::endl;
	/*try {
		v6.reserve(2305843009213693952); // length_error exception
		std::cout << "vector max size: " << v6.max_size() << std::endl;
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		v6.reserve(2305843009213693950); // bad_alloc exception
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}*/

	// cplusplus resize test
	vector<std::string> myvector;
	// set some initial content:
	for (int i=1;i<7;i++) {
		std::string str;
		str.push_back('0' + i);
		myvector.push_back(str);
	}

	std::cout << myvector.size() << " " << myvector.capacity() << std::endl;
	myvector.resize(5);
	std::cout << myvector.size() << " " << myvector.capacity() << std::endl;
	myvector.resize(8, "100");
	std::cout << myvector.size() << " " << myvector.capacity() << std::endl;
	myvector.resize(12);
	std::cout << myvector.size() << " " << myvector.capacity() << std::endl;

	std::cout << "myvector contains:";
	for (vector<std::string>::size_type i=0;i<myvector.size();i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	std::cout << "RESIZE: VOID TEST" << std::endl;
	vector<std::string> vr;
	resize_test(vr);
				    
	std::cout << "RESIZE: FILLED TEST" << std::endl;
	vector<std::string> vr1(7);
	for (vector<std::string>::size_type i = 1; i <= 7; i++)
		vr1[i - 1] = i;
	resize_test(vr1);

	std::cout << "INSERT TESTS" << std::endl;
	vector<std::string> v8(4, "42");
	print_capacity(v8);
	std::cout << *v8.insert(v8.begin() + 2, "99") << std::endl;
	print_capacity(v8);
	for (vector<std::string>::iterator it = v8.begin(); it != v8.end(); it++)
		std::cout << *it << std::endl;
	vector<std::string> v9(4, "42");
	print_capacity(v9);
	v9.insert(v9.begin() + 2, 4, "99"); // segfault with fsanitize
	print_capacity(v9);
	std::cout << "v9 content" << std::endl;
	for (vector<std::string>::iterator it = v9.begin(); it != v9.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	/*vector<std::string> v10(4, 42);
	print_capacity(v10);
	v10.insert(v10.begin() + 2, v9.begin(), v9.end());
	print_capacity(v10);
	std::cout << "v10 content" << std::endl;
	for (vector<std::string>::iterator it = v10.begin(); it != v10.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;*/

	std::cout << "data() tests" << std::endl;
	vector<std::string>::value_type *p1 = v8.data();
	const vector<std::string>::value_type *p2 = vc.data();
	vector<std::string>::pointer p3 = v8.data();
	std::cout << p1[0] << " " << p2[1] << " " << p3[2] << std::endl;

	std::cout << "erase tests" << std::endl;
	vector<std::string> v11;
	for (int i = 0; i < 5; i++) {
		std::string str;
		str.push_back('0' + i + 1);
		v11.push_back(str);
	}
	print_capacity(v11);
	std::cout << *v11.erase(v11.begin() + 2) << std::endl;
	print_capacity(v11);
	for (vector<std::string>::iterator it = v11.begin(); it != v11.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	vector<std::string> v12;
	for (int i = 0; i < 8; i++) {
		std::string str;
		str.push_back('0' + i + 1);
		v12.push_back(str);
	}
	print_capacity(v12);
	std::cout << *v12.erase(v12.begin() + 2, v12.begin() + 5) << std::endl;
	print_capacity(v12);
	for (vector<std::string>::iterator it = v12.begin(); it != v12.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "swap tests" << std::endl;
	vector<std::string> v13(3, "100");
	vector<std::string> v14;
	print_capacity(v13);
	print_capacity(v14);
	v13.swap(v14);
	print_capacity(v13);
	print_capacity(v14);
	for (vector<std::string>::iterator it = v13.begin(); it != v13.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	//std::cout << *v13.end() << std::endl;
	for (vector<std::string>::iterator it = v14.begin(); it != v14.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	//std::cout << *v14.end() << std::endl; // segfault with fsanitize

	vector<std::string> v15(3, "100");
	vector<std::string> v16(5, "200");
	print_capacity(v15);
	print_capacity(v16);
	swap(v15, v16);
	print_capacity(v15);
	print_capacity(v16);
	for (vector<std::string>::iterator it = v15.begin(); it != v15.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	//std::cout << *v15.end() << std::endl;
	for (vector<std::string>::iterator it = v16.begin(); it != v16.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	//std::cout << *v16.end() << std::endl;

	vector<std::string> v17;
	print_capacity(v17);
	v17.clear();
	print_capacity(v17);

	vector<std::string> v18(5, "2");
	print_capacity(v18);
	v18.clear();
	print_capacity(v18);
	v18.get_allocator();

	std::cout << "Relation operator" << std::endl;
	vector<std::string> v19(5, "19");
	vector<std::string> v20(v19);
	v19.push_back("19");
	v20.push_back("20");
	std::cout << (v19 == v20) << std::endl;
	std::cout << (v19 != v20) << std::endl;
	std::cout << (v19 <  v20) << std::endl;
	std::cout << (v19 <= v20) << std::endl;
	std::cout << (v19 >  v20) << std::endl;
	std::cout << (v19 >= v20) << std::endl;
	// Range constructor
	/*vector<std::string> v0(v3.begin(), v3.end());
	std::cout << "v0 Range constructor: ";
	for (vector<std::string>::iterator it = v0.begin(); it != v0.end(); it++)
	std::cout << *it << " ";
	std::cout << std::endl;*/
	return (0);
}

// apres avoir fini ce main, tu peux faire l'operator= et le constructeur de copie
// (qui sont codes par defaut par le c++, donc n'hesite pas a ajouter des cout dedans
// pour verifier qu'il vient bien dans le tien)
