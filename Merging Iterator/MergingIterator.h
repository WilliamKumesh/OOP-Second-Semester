#pragma once
#include <vector>
#include <optional>
#include "IteratorRange.h"
#include <iterator>
#include "MergingIteratorConcepts.h"

template<class InputIt>
	requires IsForwardIterator<InputIt> && HasLessFunc<InputIt>
class MergingIterator final
{
	std::vector<IteratorRange<InputIt>> iterators;
	InputIt current_it;
	
	void increment()
	{
		auto first_non_null = std::find_if(iterators.begin(), iterators.end(), [](IteratorRange<InputIt> range) {return range.getCurrent() != range.getEnd(); });

		if(first_non_null == iterators.end())
		{
			throw std::out_of_range("Out of range");
		}

		for (auto it = first_non_null + 1 ; it != iterators.end(); ++it)
		{
			if (it->getCurrent() == it->getEnd())
			{
				continue;
			}

			auto value = it->getCurrent();

			if (*value < *first_non_null->getCurrent())
			{
				first_non_null = it;
			}
		}
		current_it = first_non_null->getCurrent()++;
	}
public:
	using difference_type = std::ptrdiff_t;
	using reference = typename std::iterator_traits<InputIt>::reference;
	using pointer = typename std::iterator_traits<InputIt>::pointer;
	using iterator_category = std::forward_iterator_tag;
	using value_type = typename std::iterator_traits<InputIt>::value_type;

	MergingIterator(std::initializer_list<IteratorRange<InputIt>> iterators_list) noexcept
	{
		for(auto it: iterators_list)
		{
			if(it.getCurrent() != it.getEnd())
			{
				iterators.push_back(it);
			}
		}

		if(iterators.size() == 0)
		{
			current_it = InputIt{};
			return;
		}

		increment();
	}

	[[nodiscard]]const value_type& operator*() const
	{
		if(iterators.size() == 0)
		{
			throw std::out_of_range("Empty iterator");
		}
		return *current_it;
	}

	InputIt& operator++()
	{
		increment();
		return current_it;
	}

	InputIt operator++(int)
	{
		auto prev = current_it;
		increment();
		return prev;
	}
};