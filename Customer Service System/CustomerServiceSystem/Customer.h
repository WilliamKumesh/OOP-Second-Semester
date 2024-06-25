#pragma once
#include "Ticket.h"

enum CustomerState
{
	InOrder, InOffice, Served
};

class Customer final
{
	Ticket ticket_num;
	CustomerState state = InOrder;
public:
	Customer(Ticket ticket_num) : ticket_num(ticket_num)
	{}

	Ticket get_ticket() const noexcept
	{
		return ticket_num;
	}

	void set_state(CustomerState new_state) noexcept
	{
		state = new_state;
	}

	CustomerState get_state() const noexcept
	{
		return state;
	}
};