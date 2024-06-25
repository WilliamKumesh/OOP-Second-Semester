#pragma once
#include <iterator>

template<typename T>
concept IsForwardIterator = requires(T it)
{
	{it++} -> std::same_as<T>;
};

template<typename T>
concept HasLessFunc = requires(typename std::iterator_traits<T>::value_type a, typename std::iterator_traits<T>::value_type b)
{
	a < b;
};