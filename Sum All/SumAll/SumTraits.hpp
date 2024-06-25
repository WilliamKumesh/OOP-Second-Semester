#pragma once
#include <string>
#include <unordered_map>

template <class ValueType>
class SumTraits
{
public:
	using ResultType = ValueType;
};

template<>
class SumTraits<char>
{
public:
	using ResultType = std::string;
};

template<>
class SumTraits<std::string>
{
public:
	using ResultType = std::string;
};

template<>
class SumTraits<short>
{
public:
	using ResultType = int;
};

template<>
class SumTraits<int>
{
public:
	using ResultType = long long;
};

template<>
class SumTraits<double>
{
public:
	using ResultType = long double;
};