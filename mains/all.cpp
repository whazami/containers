#include <iostream>
#include <string>

#ifdef MINE
	#include "../containers/vector.hpp"
	#include "../utils/pair.hpp"
#else
	#include <vector>
	#include <utility>
#endif

using namespace NAMESPACE;

#define TESTED_TYPE std::string
#define TESTED_TYPE2 foo<int>

// --- Class foo
template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}
// --- End of class foo

void printSize(vector<TESTED_TYPE> v) {
	std::cout << v.size() << " " << v.capacity() << std::endl;
}

void printSize(const vector<TESTED_TYPE2>& v, int i) {
	(void)i;
	std::cout << v.size() << " " << v.capacity() << std::endl;
}

void	checkErase(vector<TESTED_TYPE> const &vct,
					vector<TESTED_TYPE>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	printSize(vct);
}

void printSize(vector<int> v) {
	std::cout << v.size() << " " << v.capacity() << std::endl;
}

void print_capacity(vector<int> v)
{
	std::cout << v.size() << " " << v.capacity() << std::endl;
}

void print_capacity(vector<std::string> v)
{
	std::cout << v.size() << " " << v.capacity() << std::endl;
}

void resize_test(vector<int> v)
{
    std::cout << v.capacity() << std::endl;
	v.resize(6);
	std::cout << v.capacity() << std::endl;
	v.resize(0);
	std::cout << v.capacity() << std::endl;
	v.resize(9, 100);
	std::cout << v.capacity() << std::endl;
	v.resize(13);
	std::cout << v.capacity() << std::endl;
	v.resize(27);
	std::cout << v.capacity() << std::endl;
											    
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
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
	/// --- main.cpp --- ///
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
	vvs[5].reserve(7);
	std::cout << vvs[5].size() << " " << vvs[5].capacity() << std::endl;
	vvs[6].resize(5, 100);
	std::cout << vvs[6].size() << " " << vvs[6].capacity() << std::endl;
	for (vector<float>::iterator it = vvs[6].begin(); it != vvs[6].end(); it++)
		std::cout << *it << std::endl;
	std::cout << "yooyoo test" << std::endl;
	vvs[7].insert(vvs[7].begin(), 9);
	std::cout << vvs[7].front() << std::endl;
	vvs[8].insert(vvs[8].begin(), 5, 21.f);
	std::cout << vvs[8].size() << " " << vvs[8].capacity() << std::endl;
	for (vector<float>::iterator it = vvs[8].begin(); it != vvs[8].end(); it++)
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
	vector<int> myvector;
	// set some initial content:
	for (int i=1;i<7;i++) myvector.push_back(i);

	std::cout << myvector.size() << " " << myvector.capacity() << std::endl;
	myvector.resize(5);
	std::cout << myvector.size() << " " << myvector.capacity() << std::endl;
	myvector.resize(8,100);
	std::cout << myvector.size() << " " << myvector.capacity() << std::endl;
	myvector.resize(12);
	std::cout << myvector.size() << " " << myvector.capacity() << std::endl;

	std::cout << "myvector contains:";
	for (vector<int>::size_type i=0;i<myvector.size();i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	std::cout << "RESIZE: VOID TEST" << std::endl;
	vector<int> vr;
	resize_test(vr);
				    
	std::cout << "RESIZE: FILLED TEST" << std::endl;
	vector<int> vr1(7);
	for (vector<int>::size_type i = 1; i <= 7; i++)
		vr1[i - 1] = i;
	resize_test(vr1);

	std::cout << "INSERT TESTS" << std::endl;
	vector<int> v8(4, 42);
	print_capacity(v8);
	std::cout << *v8.insert(v8.begin() + 2, 99) << std::endl;
	print_capacity(v8);
	for (vector<int>::iterator it = v8.begin(); it != v8.end(); it++)
		std::cout << *it << std::endl;
	vector<int> v9(4, 42);
	print_capacity(v9);
	v9.insert(v9.begin() + 2, 4, 99); // segfault with fsanitize
	print_capacity(v9);
	std::cout << "v9 content" << std::endl;
	for (vector<int>::iterator it = v9.begin(); it != v9.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	vector<int> v10(4, 42);
	print_capacity(v10);
	v10.insert(v10.begin() + 2, v9.begin(), v9.end());
	print_capacity(v10);
	std::cout << "v10 content" << std::endl;
	for (vector<int>::iterator it = v10.begin(); it != v10.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "data() tests" << std::endl;
	vector<int>::value_type *p1 = v8.data();
	const vector<int>::value_type *p2 = vc.data();
	vector<int>::pointer p3 = v8.data();
	std::cout << p1[0] << " " << p2[1] << " " << p3[2] << std::endl;

	std::cout << "erase tests" << std::endl;
	vector<int> v11;
	for (int i = 0; i < 5; i++)
		v11.push_back(i + 1);
	print_capacity(v11);
	std::cout << *v11.erase(v11.begin() + 2) << std::endl;
	print_capacity(v11);
	for (vector<int>::iterator it = v11.begin(); it != v11.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	vector<int> v12;
	for (int i = 0; i < 8; i++)
		v12.push_back(i + 1);
	print_capacity(v12);
	std::cout << *v12.erase(v12.begin() + 2, v12.begin() + 5) << std::endl;
	print_capacity(v12);
	for (vector<int>::iterator it = v12.begin(); it != v12.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "swap tests" << std::endl;
	vector<int> v13(3, 100);
	vector<int> v14;
	print_capacity(v13);
	print_capacity(v14);
	v13.swap(v14);
	print_capacity(v13);
	print_capacity(v14);
	for (vector<int>::iterator it = v13.begin(); it != v13.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	//std::cout << *v13.end() << std::endl;
	for (vector<int>::iterator it = v14.begin(); it != v14.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	//std::cout << *v14.end() << std::endl; // segfault with fsanitize

	vector<int> v15(3, 100);
	vector<int> v16(5, 200);
	print_capacity(v15);
	print_capacity(v16);
	swap(v15, v16);
	print_capacity(v15);
	print_capacity(v16);
	for (vector<int>::iterator it = v15.begin(); it != v15.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	//std::cout << *v15.end() << std::endl;
	for (vector<int>::iterator it = v16.begin(); it != v16.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	//std::cout << *v16.end() << std::endl;

	vector<int> v17;
	print_capacity(v17);
	v17.clear();
	print_capacity(v17);

	vector<int> v18(5, 2);
	print_capacity(v18);
	v18.clear();
	print_capacity(v18);
	v18.get_allocator();

	std::cout << "Relation operator" << std::endl;
	vector<int> v19(5, 19);
	vector<int> v20(v19);
	v19.push_back(19);
	v20.push_back(20);
	std::cout << (v19 == v20) << std::endl;
	std::cout << (v19 != v20) << std::endl;
	std::cout << (v19 <  v20) << std::endl;
	std::cout << (v19 <= v20) << std::endl;
	std::cout << (v19 >  v20) << std::endl;
	std::cout << (v19 >= v20) << std::endl;
	// Range constructor
	vector<float> v0(v3.begin(), v3.end());
	std::cout << "v0 Range constructor: ";
	for (vector<float>::iterator it = v0.begin(); it != v0.end(); it++)
	std::cout << *it << " ";
	std::cout << std::endl;
	}
	/// --- main_string.cpp --- ///
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
	vector<std::string> v10(4, "42");
	print_capacity(v10);
	v10.insert(v10.begin() + 2, v9.begin(), v9.end());
	print_capacity(v10);
	std::cout << "v10 content" << std::endl;
	for (vector<std::string>::iterator it = v10.begin(); it != v10.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

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
	vector<std::string> v0(v3.begin(), v3.end());
	std::cout << "v0 Range constructor: ";
	for (vector<std::string>::iterator it = v0.begin(); it != v0.end(); it++)
	std::cout << *it << " ";
	std::cout << std::endl;
	}
	/// --- yooyoo.cpp --- ///
	{
	vector<int> myvector (3,100);
	vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert ( it , 200 );

	myvector.insert (it,2,300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	vector<int> anothervector (2,400);
	myvector.insert (it+2,anothervector.begin(),anothervector.end());

	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), myarray, myarray+3);

	std::cout << "myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
	}
	/// --- assign.cpp --- ///
	{
	vector<int> vct(7);
	vector<int> vct_two(4);
	vector<int> vct_three;
	vector<int> vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;
	printSize(vct);
	printSize(vct_two);

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###" << std::endl;

	printSize(vct);
	printSize(vct_two);
	printSize(vct_three);
	printSize(vct_four);

	vct_four.assign(6, 84);
	printSize(vct_four);

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

	printSize(vct);
	printSize(vct_two);
	}
	/// --- erase.cpp --- ///
	{
	vector<TESTED_TYPE> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	printSize(vct);

	checkErase(vct, vct.erase(vct.begin() + 2));

	checkErase(vct, vct.erase(vct.begin()));
	checkErase(vct, vct.erase(vct.end() - 1));

	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	printSize(vct);
	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	printSize(vct);
	checkErase(vct, vct.erase(vct.begin(), vct.end()));
	}
	/// --- ite_arrow --- ///
	{
	const int size = 5;
	vector<TESTED_TYPE2> vct(size);
	vector<TESTED_TYPE2>::iterator it(vct.begin());
	vector<TESTED_TYPE2>::const_iterator ite(vct.end());

	for (int i = 1; it != ite; ++i)
		*it++ = i;
	printSize(vct, 1);

	it = vct.begin();
	ite = vct.begin();

	std::cout << *(++ite) << std::endl;
	std::cout << *(ite++) << std::endl;
	std::cout << *ite++ << std::endl;
	std::cout << *++ite << std::endl;

	it->m();
	ite->m();

	std::cout << *(++it) << std::endl;
	std::cout << *(it++) << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *++it << std::endl;

	std::cout << *(--ite) << std::endl;
	std::cout << *(ite--) << std::endl;
	std::cout << *--ite << std::endl;
	std::cout << *ite-- << std::endl;

	(*it).m();
	(*ite).m();

	std::cout << *(--it) << std::endl;
	std::cout << *(it--) << std::endl;
	std::cout << *it-- << std::endl;
	std::cout << *--it << std::endl;
	}
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
	}
	return 0;
}
