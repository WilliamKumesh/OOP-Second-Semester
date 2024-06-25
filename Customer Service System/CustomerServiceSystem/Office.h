#pragma once
#include <future>
#include <mutex>
#include <vector>
#include "Customer.h"
#include "CustomerServiceTable.h"
#include "ThreadPool.h"

class Office
{
	std::vector<CustomerServiceTable> tables;
	ThreadPool pool;
	std::mutex mutex;

	size_t get_available_table() const noexcept;
public:

	explicit Office(size_t tables_num, std::chrono::milliseconds table_waiting_time);

	void serve_customer(Customer& customer);
};