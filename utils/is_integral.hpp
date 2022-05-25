#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include <iostream>
#include <uchar.h>

namespace ft
{
	template <class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
	};

	template <class T>
	struct is_integral : public integral_constant<bool, false> {};
	template <>
	struct is_integral<bool> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<char> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<wchar_t> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<signed char> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<short int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<long int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<unsigned char> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<unsigned short int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<unsigned int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<unsigned long int> : public integral_constant<bool, true> {};

	// const
	template <>
	struct is_integral<const bool> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const char> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const wchar_t> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const signed char> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const short int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const long int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const unsigned char> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const unsigned short int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const unsigned int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const unsigned long int> : public integral_constant<bool, true> {};

	// volatile
	template <>
	struct is_integral<volatile bool> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<volatile char> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<volatile wchar_t> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<volatile signed char> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<volatile short int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<volatile int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<volatile long int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<volatile unsigned char> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<volatile unsigned short int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<volatile unsigned int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<volatile unsigned long int> : public integral_constant<bool, true> {};

	// const volatile
	template <>
	struct is_integral<const volatile bool> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const volatile char> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const volatile wchar_t> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const volatile signed char> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const volatile short int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const volatile int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const volatile long int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const volatile unsigned char> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const volatile unsigned short int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const volatile unsigned int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<const volatile unsigned long int> : public integral_constant<bool, true> {};
}

#endif // IS_INTEGRAL_HPP
