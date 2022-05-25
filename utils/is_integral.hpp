#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include <iostream>

namespace ft
{
	template <typename T, typename U>
	struct is_same {
		static const bool value = false;
	};
	template <typename T>
	struct is_same<T, T> {
		static const bool value = true;
	};

	template <class T>
	struct is_integral
	{
			typedef bool	value_type;
			
			const static value_type value = ft::is_same<T, int>::value;
	};
}

#endif // IS_INTEGRAL_HPP
