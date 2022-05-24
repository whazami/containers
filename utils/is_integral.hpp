#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include <iostream>
#include <type_traits>

namespace ft
{
	template <class T>
	class is_integral
	{
		public:
			typedef bool value_type;
			static value_type value;

			is_integral() {
			}

		private:
			std::integral_constant<int, 0> ic;
	};

	template <class T>
	typename is_integral<T>::value_type is_integral<T>::value = false;
}

#endif // IS_INTEGRAL_HPP
