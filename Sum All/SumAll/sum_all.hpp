#pragma once
#include "SumTraits.hpp"
#include <type_traits>

namespace enable_sum
{
	template<template<class, class> class Container, class Type, class Allocator>
	concept IsContainer = std::is_same_v<decltype(std::declval<Container<Type, Allocator>>().begin()), typename Container<Type, Allocator>::iterator>;


	template<template<class, class, class, class> class Container, class Key, class Type,
		class Traits = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, Type>>>
		concept IsMap = std::is_same_v<decltype(std::declval<Container<Key, Type, Traits, Allocator>>().begin()), typename Container<Key, Type, Traits, Allocator>::iterator>;


	template <class ValueType>
	ValueType SumAll(const ValueType& value)
	{
		ValueType result = value;
		return result;
	}

	template<template<class, class> class Container, class Type, class Allocator, typename = std::enable_if<IsContainer<Container, Type, Allocator>>,
		class ResultType = typename SumTraits<Type>::ResultType>
		ResultType SumAll(const Container<Type, Allocator>& container)
	{
		ResultType sum{};

		for (const auto& elem : container)
		{
			sum += elem;
		}
		return sum;
	}

	template<template<class, class, class, class> class Container, class Key, class Type, class Traits = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, Type>>,
	typename = std::enable_if<IsMap<Container, Key, Type, Traits, Allocator>>, class ResultType = typename SumTraits<Type>::ResultType>
	ResultType SumAll(const Container<Key, Type, Traits, Allocator>& container)
	{
		ResultType sum{};

		for (const auto& [key, value] : container)
		{
			sum += value;
		}
		return sum;
	}
}