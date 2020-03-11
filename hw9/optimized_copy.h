#ifndef OPTIMIZED_COPY_H
#define OPTIMIZED_COPY_H
#include<type_traits>
#include<iterator>
using std::iterator_traits;
using std::integral_constant;
using std::true_type;
using std::enable_if_t;
using std::remove_const_t;
using std::is_trivially_copy_constructible_v;

namespace mpcs {

	template<typename I1, typename I2>
	I2 optimized_copy(I1 first, I1 last, I2 out)
	{

		while (first != last)
		{
			*out = *first;
			++out;
			++first;
		}
		return out;
	}

	template<typename T, enable_if_t<is_trivially_copy_constructible_v<T>> * = nullptr>
	remove_const_t<T>* optimized_copy(T* first, T* last, remove_const_t<T>* out)
	{
		memcpy(out, first, (last - first) * sizeof(T));
		return out + (last - first);
	}
}
#endif // !OPTIMIZED_COPY_H
