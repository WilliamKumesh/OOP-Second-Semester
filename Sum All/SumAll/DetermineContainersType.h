#pragma once

template<class Container>
	requires std::ranges::range<Container>
struct DetermineMapDataType
{
	using value_type = decltype(std::declval<Container>().begin()->second);
};

template<class Container>
	requires std::ranges::range<Container>
struct DetermineContainerDataType
{
	using value_type = typename  std::iterator_traits<decltype(std::declval<Container>().begin())>::value_type;
};