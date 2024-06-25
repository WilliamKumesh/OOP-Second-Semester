#include "CustomerServiceTable.h"
#include <iostream>
#include <thread>
#include <string>

CustomerServiceTable::CustomerServiceTable(std::chrono::milliseconds time_sleep, size_t table_num) : time_sleep(time_sleep), table_num(table_num)
{}

void CustomerServiceTable::work(const Customer& customer)
{
	ServiceLogger::log(std::cout, "Table " + std::to_string(table_num) + " start serving customer " + std::to_string(customer.get_ticket().get_number()) + '\n');
	std::this_thread::sleep_for(time_sleep);
	ServiceLogger::log(std::cout, "Customer " + std::to_string(customer.get_ticket().get_number()) + " has been served at table " + std::to_string(table_num) + '\n');

	state = Free;
	//customer.set_state(Served);
}

size_t CustomerServiceTable::get_table_num() const noexcept
{
	return table_num;
}

void CustomerServiceTable::set_state() noexcept
{
	state = Busy;
}

TableState CustomerServiceTable::get_state() const noexcept
{
	return state;
}
