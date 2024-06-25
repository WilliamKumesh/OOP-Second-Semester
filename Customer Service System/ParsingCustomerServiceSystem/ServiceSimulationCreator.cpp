#include "ServiceSimulationCreator.h"
#include <sstream>

namespace 
{
	constexpr size_t elem_num = 4;

	enum parsing_order { num_table, max_customers, time_customer_entry, time_table_serve };
}

SimulatorServiceSystem ServiceSystemSimulationCreator::create_service_system(std::istream& in)
{
	std::string parsing_stream;
	std::vector<size_t> parsing_data;

	for(size_t i = 0; i < elem_num; i++)
	{
		in >> parsing_stream;
		std::stringstream ss(parsing_stream);

		size_t data;
		ss >> data;

		parsing_data.push_back(data);
	}

	return { parsing_data[num_table], parsing_data[max_customers], static_cast<std::chrono::milliseconds>(parsing_data[time_customer_entry]),
		static_cast<std::chrono::milliseconds>(parsing_data[time_table_serve]) };
}