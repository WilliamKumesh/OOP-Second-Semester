#pragma once
#include "SimulatorServiceSystem.h"

class ServiceSystemSimulationCreator final
{
public:
	ServiceSystemSimulationCreator() = delete;

	static SimulatorServiceSystem create_service_system(std::istream& in);
};