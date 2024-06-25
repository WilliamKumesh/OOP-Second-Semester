#pragma once

template<class InputIt>
class IteratorRange final
{
	InputIt current;
	InputIt end;
public:
	IteratorRange(InputIt begin_, InputIt end_): current(std::move(begin_)), end(std::move(end_))
	{}

	InputIt& getCurrent() noexcept
	{
		return current;
	}

	const InputIt& getEnd() const noexcept
	{
		return end;
	}
};