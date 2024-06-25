#pragma once
#include "Office.h"
#include "CustomerProvider.h"

class SimulatorServiceSystem
{
	Office office;
	size_t max_customers;
	CustomerProvider provider;

public:
	SimulatorServiceSystem(size_t num_tables, size_t max_customers, std::chrono::milliseconds time_customer_entry, 
	std::chrono::milliseconds table_waiting_time): office(num_tables, table_waiting_time),max_customers(max_customers), provider(max_customers, time_customer_entry)
	{}

	void run_simulation();
};
