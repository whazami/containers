#include <iostream>
#include <unistd.h>

#ifdef MINE
	#include "../../containers/vector.hpp"
	#include "../../containers/stack.hpp"
#else
	#include <vector>
	#include <stack>
#endif

using namespace NAMESPACE;

#define CYAN "\033[0;36m"
#define END_COLOR "\033[0m"
#define MAGENTA "\033[0;35m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"


int main()
{
	////////////////////// TEST REVERSE_ITERATOR ////////////////////////
	
	std::cout << std::endl << CYAN << "********** Test Reverse Iterator **********" << END_COLOR << std::endl << std::endl;

	std::cout << YELLOW << "Test 1: An empty constructor" << END_COLOR << std::endl;
	reverse_iterator<vector<int>::iterator> empty;
	std::cout << GREEN << "The Empty constructor compile !" << END_COLOR << std::endl;

	std::cout << std::endl << YELLOW << "Test 2:" << END_COLOR << std::endl;
	vector<int> vec(5, 7);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	std::cout << "Iterator vec : ";
    for(vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	        std::cout << *it << " ";
	std::cout << std::endl;	
	std::cout << "Reverse Iterator vec without boucle for: ";
	reverse_iterator<vector<int>::iterator> rit = vec.rbegin();
	std::cout << *rit << " ";
	rit++;
	std::cout << *rit << " ";
	rit++;
	std::cout << *rit << " ";
	rit++;
	std::cout << *rit << " ";
	rit++;
	std::cout << *rit << " " << std::endl;
	rit = vec.rend() - 1;
	//std::cout << "coucou ";
	//std::cout << &(*vec.rend()) << std::endl;
	//std::cout << &(*rit);
	//std::cout << " coucou" << std::endl;
	std::cout << "vec.rend() - vec.rbegin(): " << vec.rend() - vec.rbegin() << std::endl;
	std::cout << "rend() du vector: " << *vec.rend() << std::endl;
	std::cout << "rend() - 1 du vector: " << *rit << std::endl;
	std::cout << "Reverse Iterator vec with boucle for: ";
    for(reverse_iterator<vector<int>::iterator> it = vec.rbegin(); it != vec.rend() - 1; it++)
    {
		//write(1, "heyy ", 5); // to DEBUG
		std::cout << *it << " ";
	}
	std::cout << std::endl << std::endl;
	

	std::cout << YELLOW << "Test 3: " << END_COLOR << std::endl;

	vector<int>::iterator from(vec.begin());
	vector<int>::iterator until(vec.end());
	reverse_iterator<vector<int>::iterator> rev_end(from);
	reverse_iterator<vector<int>::iterator> rev_begin(until);
	/*std::cout << "Compare adress of iterator vec.begin() and rev iterator(vec.begin()): " << std::endl;
	std::cout << &(*from) << " and ";
	std::cout << &(*rev_end) << std::endl;
	std::cout << "Compare adress of iterator vec.end() and rev iterator(vec.end()): " << std::endl;
	std::cout << &(*until) << " and ";
	std::cout << &(*rev_begin) << std::endl;
	std::cout << GREEN << "It works! They need to be different!" << END_COLOR << std::endl << std::endl;
	*/
	std::cout << "rev_end to rev_begin: ";	
	while (rev_end != rev_begin) {
		std::cout << *rev_begin << " ";
		rev_begin++;
	}
	std::cout << std::endl << std::endl;

	std::cout << YELLOW << "Test 4: Base " << END_COLOR << std::endl << "rev.base(): "; 
	std::cout << *rev_end.base() << std::endl; 
	for(reverse_iterator<vector<int>::iterator> rit = vec.rbegin(); rit != vec.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << std::endl << std::endl;


	std::cout << YELLOW << "Test 5: Constructors " << END_COLOR << std::endl;
	vector<float> v5(5, 42);
	// test default constructor
	std::cout << "test default constructor: " << std::endl;
	reverse_iterator<vector<int>::iterator> r;
	std::cout << GREEN << "The Default constructor compile !" << END_COLOR << std::endl;
	std::cout << std::endl;

	// test constructor 1
	std::cout << "test initialization constructor: " << std::endl;
	reverse_iterator<vector<float>::iterator> rev1(v5.begin());
	vector<float>::iterator i = v5.end();
	reverse_iterator<vector<float>::iterator> rev2(i);
	reverse_iterator<vector<float>::iterator> rev3(reverse_iterator<vector<float>::iterator> b);
	std::cout << GREEN << "The initialization constructor compile !" << END_COLOR << std::endl;
	std::cout << std::endl;
	
	//test operator=
	std::cout << "test operator=() and operator*(): " << std::endl;
	vector<float> vct;
	vector<float>::iterator it = vct.begin(); (void)it;
	vector<float>::reverse_iterator rit2(it);
	vector<float>::const_reverse_iterator crit(rit2);
	std::cout << GREEN << "The operator=() and operator*() works !" << END_COLOR << std::endl;
	std::cout << std::endl;
	// test constructor copy
	std::cout << "test copy constructor() " << std::endl;
	vector<float>::const_reverse_iterator crit2(rit2);
	std::cout << GREEN << "The copy constructor works !" << END_COLOR << std::endl;
	std::cout << std::endl;


	std::cout << YELLOW << "Test 6: Members Overload operators " << END_COLOR << std::endl;
	
	std::cout << "Display vector vct reverse: ";
	vct.push_back(1);
	vct.push_back(2);
	vct.push_back(3);
	vct.push_back(4);
	vct.push_back(5);
	vct.push_back(11);
	vct.push_back(12);
	vct.push_back(13);
	vct.push_back(14);
	vct.push_back(15);
	for(reverse_iterator<vector<float>::iterator> rit = vct.rbegin(); rit != vct.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << std::endl;
	std::cout << "Create a reverse iterator rit from vct.rbegin() " << std::endl;
	vector<float>::reverse_iterator rit3(vct.rbegin());
	std::cout << "And increment and decrement it with operators ++,--,+=,-=,+,-: " << std::endl;
	rit3 = rit3 + 2;
	std::cout << "Increment rit + 2: " << *rit3 << std::endl;
	rit3 = rit3 - 2;
	std::cout << "Decrement rit - 2: " << *rit3 << std::endl;
	rit3++;
	rit3++;
	rit3++;
	rit3++;
	std::cout << "Increment rit++ 4 times: " << *rit3 << std::endl;
	rit3--;
	std::cout << "Decrement rit--: " << *rit3 << std::endl;
	rit3 += 2;
	std::cout << "Increment rit += 2: "<< *rit3 << std::endl;
	std::cout << "Increment rit += 2: "<< *(rit3 += 2) << std::endl;
	rit3 -= 2;
	std::cout << "Decrement rit-=2: " << *rit3 << std::endl;
	std::cout << "Decrement rit-=2: " << *(rit3 -= 2) << std::endl;
	std::cout << GREEN << "The assignment, increment, decrement " << std::endl << "and arithmetic operators work!" << END_COLOR << std::endl;
	std::cout << std::endl;
	vector<float> vct1;
	vct1.push_back(4);
	vct1.push_back(5);
	vct1.push_back(6);
	vct1.push_back(7);
	vct1.push_back(8);
	vct1.push_back(9);
	for(reverse_iterator<vector<float>::iterator> rit = vct1.rbegin(); rit != vct1.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << std::endl;
	vector<float>::reverse_iterator rit5(vct1.rbegin());
	std::cout << "test -= and += with reverse_iterator" << std::endl;
	rit5 += 2;
	std::cout << "Increment rit += 2: "<< *rit5 << std::endl;
	std::cout << "Increment rit += 2: "<< *(rit5 += 2) << std::endl;
	rit5 -= 2;
	std::cout << "Decrement rit-=2: " << *rit5 << std::endl;
	std::cout << "Decrement rit-=2: " << *(rit5 -= 2) << std::endl;
	
	std::cout << std::endl;
	vector<float>::const_reverse_iterator rit4(vct1.rbegin());
	std::cout << "test -= and += with const reverse_iterator" << std::endl;
	std::cout << *rit4 << std::endl;
	rit4 += 2;
	std::cout << "Increment rit += 2: "<< *rit4 << std::endl;
	std::cout << "Increment rit += 2: "<< *(rit4 += 2) << std::endl;
	rit4 -= 2;
	std::cout << "Decrement rit-=2: " << *rit4 << std::endl;
	std::cout << "Decrement rit-=2: " << *(rit4 -= 2) << std::endl;
	std::cout << std::endl;	

	std::cout << YELLOW << "Test 7: Non Members Overload operators " << END_COLOR << std::endl;
	
	std::cout << "Test on rit the non member relational operators: " << std::endl;// "and the operator->(): " << std::endl;
	vector<int> re(4,2);
	std::cout << "Create a const reverse iterator lhs and non const rhs which are different " << std::endl << std::endl;
	const reverse_iterator<vector<int>::iterator> lhs = re.rbegin();
	reverse_iterator<vector<int>::iterator> rhs;
	if (lhs != rhs)
		std::cout << "Test to compare if lhs != rhs" << std::endl << GREEN << "valid!" << std::endl << END_COLOR << std::endl;	
	if (lhs == rhs)
		std::cout << MAGENTA << "Compare if lhs == rhs invalid!" << std::endl << END_COLOR << std::endl;
	std::cout << "Compare if lhs == rhs " << std::endl << GREEN << "valid, they still not equal!" << std::endl << END_COLOR << std::endl;
	std::cout << "rhs becomes equal to lhs:" << std::endl;
	rhs = lhs;
	if (lhs == rhs)
		std::cout << "Compare if lhs == rhs" << std::endl << GREEN << "valid!" << std::endl << END_COLOR << std::endl;
	vector<int> ree(3,1);
	const reverse_iterator<vector<int>::iterator> rhss(ree.begin());
	std::cout << "Change the content of rhs:" << std::endl;
	std::cout << "Compare if lhs < rhs" << std::endl;
	std::cout << ((lhs < rhss) ? MAGENTA : GREEN)  << ((lhs < rhss) ? "invalid: true " : "valid: false ") << END_COLOR << (lhs < rhss) << std::endl;
	std::cout << "Compare if lhs > rhs" << std::endl;
	std::cout << ((lhs > rhss) ? GREEN : MAGENTA)  << ((lhs > rhss) ? "valid: true " : "invalid: false ") << END_COLOR << (lhs > rhss) << std::endl;
	std::cout << "Compare if lhs >= rhs" << std::endl;
	std::cout << ((lhs >= rhss) ? GREEN : MAGENTA)  << ((lhs >= rhss) ? "valid: true " : "invalid: false ") << END_COLOR << (lhs >= rhss) << std::endl;
	std::cout << "Compare if lhs <= rhs" << std::endl;
	std::cout << ((lhs <= rhss) ? MAGENTA : GREEN)  << ((lhs <= rhss) ? "invalid: true " : "valid: false ") << END_COLOR << (lhs <= rhss) << std::endl;
	std::cout << "Test non member operator-(): " << std::endl;
	const reverse_iterator<vector<int>::iterator> rhsss(re.begin());
	const reverse_iterator<vector<int>::iterator>::difference_type tr = lhs - rhsss;
	std::cout << tr << std::endl;
	std::cout << (lhs - rhsss) << std::endl;
	std::cout << "Test non member operator+(): " << std::endl;
	reverse_iterator<vector<int>::iterator> tr2 = 3 + rhss;
	std::cout << *tr2 << std::endl;
	std::cout << "Test template operator=(): " << std::endl;
	reverse_iterator<vector<int>::const_iterator> t3;
	t3 = rhss;
	std::cout << *t3 << std::endl;

	std::cout << std::endl;
	std::cout << YELLOW << "Test 8: Difference between pointer and base() " << END_COLOR << std::endl;
	//vector<float>::const_iterator cit = vct.begin();
	//vector<float>::const_reverse_iterator crit1(it);
    vector<int> vect;
    vect.push_back(1);
    vect.push_back(2);
    vect.push_back(3);

    reverse_iterator<vector<int>::iterator> rite(vect.rbegin() + 1);
    std::cout << *rite << " "  << *rite.base() << std::endl;
    std::cout << (*rite == *rite) << std::endl;
    std::cout << (*rite.base() != *rite.base()) << std::endl;

	return 0;
}
