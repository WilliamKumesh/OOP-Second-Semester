#pragma once
#include "Logger.h"
#include "Customer.h"

enum TableState
{
	Free, Busy
};

class CustomerServiceTable
{
	std::chrono::milliseconds time_sleep;
	size_t table_num;
	TableState state = Free;

public:
	CustomerServiceTable(std::chrono::milliseconds time_sleep, size_t table_num);

	void work(const Customer& customer);

	size_t get_table_num() const noexcept;

	void set_state() noexcept;

	TableState get_state() const noexcept;
};