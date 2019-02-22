#ifndef _UTILITIES_VARIANT_H
#define _UTILITIES_VARIANT_H

namespace app::util
{
	// Initializes a template struct named overload
	// allows a special use of std::visit shown in 
	// https://www.bfilipek.com/2018/06/variant.html#overload
	// Usage:
	//	std::variant<int, double, float> number = 1.0;
	//	std::visit(overload{
	//		[](int & num) { num += 1; },
	//		[](double & num) { num += 2.0; },
	//		[](float & num) { num += 4.0f; }
	//	}, number);
	//
	// The above will increment example will increment the variant by
	//   one if the variant is of type int;
	//   two if the variant is of type double;
	//   and four if the variant is of type float.
	//
	template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
	template<class... Ts> overload(Ts...)->overload<Ts...>;
}

#endif // !_UTILITIES_VARIANT_H
