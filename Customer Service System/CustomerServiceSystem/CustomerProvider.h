#pragma once
#include <chrono>
#include <vector>
#include "Customer.h"
#include "TicketMachine.h"

class CustomerProvider
{
	size_t max_customers;
	std::chrono::milliseconds entry_duration;

	std::vector<Customer> customers;

	TicketMachine ticket_machine{ 1 };

	inline static std::chrono::time_point<std::chrono::steady_clock> last_call_time = std::chrono::steady_clock::now();
public:
	CustomerProvider(size_t max_customers, std::chrono::milliseconds entry_time);

	bool check_duration_time() const noexcept;

	void create_new_customer();

	Customer& get_customer(size_t index);

	bool check_all_served() const;

	size_t get_current() const;
};
