#include "ServiceSimulationCreator.h"
#include <fstream>

using namespace std;

int main()
{
	std::fstream fin;
	fin.open("test.txt");
	SimulatorServiceSystem simulator = ServiceSystemSimulationCreator::create_service_system(fin);
	simulator.run_simulation();
}