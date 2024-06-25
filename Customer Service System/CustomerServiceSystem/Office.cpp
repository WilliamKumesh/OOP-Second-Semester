#include "Office.h"
#include <numeric>

Office::Office(size_t tables_num, std::chrono::milliseconds table_waiting_time) : pool(tables_num)
{
	tables.reserve(tables_num);

	for (size_t i = 0; i < tables_num; i++)
	{
		tables.emplace_back(table_waiting_time, i);
	}
}

size_t Office::get_available_table() const noexcept
{
	for (size_t i = 0; i < tables.size(); i++)
	{
		if (tables[i].get_state() == Free)
		{
			return i;
		}
	}

	return std::numeric_limits<size_t>::max();
}

void Office::serve_customer(Customer& customer)
{
	std::unique_lock lock(mutex);

	if (const size_t free_table = get_available_table(); free_table != std::numeric_limits<size_t>::max())
	{
		customer.set_state(InOffice);

		tables[free_table].set_state();
		pool.add_table_task(tables[free_table], customer);
	}
}