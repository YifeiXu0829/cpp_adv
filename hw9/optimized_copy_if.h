#ifndef OPTIMIZED_COPY_H
#define OPTIMIZED_COPY_H
#include<type_traits>
#include<iterator>
using std::iterator_traits;
using std::integral_constant;
using std::true_type;
using std::is_trivially_copy_constructible_v;
using std::is_pointer_v;
using std::is_same_v;

namespace mpcs {

	template<typename I1, typename I2>
	I2 optimized_copy(I1 first, I1 last, I2 out)
	{
		using value_type = typename iterator_traits<I2>::value_type;
		if constexpr (is_pointer_v<I1> && is_same_v<I1, I2>
			&& is_trivially_copy_constructible_v<value_type>) {
			memcpy(out, first, (last - first) * sizeof(value_type));
			return out + (last - first);
		} else {
			for (; first != last; ++out, ++first)
				*out = *first;
			return out;
		}
	}
}
#endif // !OPTIMIZED_COPY_H
