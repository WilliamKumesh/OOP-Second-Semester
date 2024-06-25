#pragma once

class Ticket
{
	size_t number;
public:
	Ticket(size_t number) : number(number)
	{}

	size_t get_number() const noexcept
	{
		return number;
	}
};