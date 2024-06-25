#include "SimulatorServiceSystem.h"

void SimulatorServiceSystem::run_simulation()
{
	size_t num_serving = 0;

	while(num_serving < max_customers)
	{
		if(!provider.check_duration_time())
		{
			continue;
		}

		provider.create_new_customer();

		while(provider.get_customer(num_serving).get_state() == InOrder)
		{
			office.serve_customer(provider.get_customer(num_serving));
		}

		++num_serving;
	}


}
