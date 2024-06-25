#include "Logger.h"
#include <ostream>
#include <ctime>
#include <syncstream>

void ServiceLogger::log(std::ostream& out, const std::string& message)
{
	const auto end = std::chrono::system_clock::now();
	const std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	char str[26];
	const auto err = ctime_s(str, sizeof str, &end_time);

	std::osyncstream(out) << str << message << std::endl;
}
