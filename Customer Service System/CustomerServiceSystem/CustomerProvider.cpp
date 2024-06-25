#include "CustomerProvider.h"
#include "Logger.h"
#include <iostream>

CustomerProvider::CustomerProvider(size_t max_customers, std::chrono::milliseconds entry_time):max_customers(max_customers), entry_duration(entry_time)
{
}

bool CustomerProvider::check_duration_time() const noexcept
{
    const auto current_time = std::chrono::steady_clock::now();
    const auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_call_time);

    return elapsed_time > entry_duration && max_customers >= customers.size();
}

void CustomerProvider::create_new_customer()
{
    customers.emplace_back(ticket_machine.take_ticket());
    ServiceLogger::log(std::cout, "Customer " + std::to_string(customers[customers.size() - 1].get_ticket().get_number()) + " enter the office\n");
}

Customer& CustomerProvider::get_customer(size_t index)
{
    last_call_time = std::chrono::steady_clock::now();
    return customers[index];
}

//bool CustomerProvider::check_all_served() const
//{
//    if(customers.size() < max_customers)
//    {
//        return false;
//    }
//
//    size_t num_served = 0;
//
//	for(const auto& it: customers)
//	{
//		if(it.get_state() == Served)
//		{
//            ++num_served;
//		}
//	}
//
//    return num_served >= max_customers;
//}
