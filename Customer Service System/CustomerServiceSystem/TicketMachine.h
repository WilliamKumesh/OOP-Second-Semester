#pragma once
#include "Ticket.h"
#include <mutex>

class TicketMachine final
{
	size_t current_ticket_num;
	std::mutex mutex;
public:
	TicketMachine(size_t initial_ticket_num): current_ticket_num(initial_ticket_num)
	{}

	Ticket take_ticket() noexcept
	{
		std::lock_guard lock(mutex);
		return { current_ticket_num++ };
	}
};