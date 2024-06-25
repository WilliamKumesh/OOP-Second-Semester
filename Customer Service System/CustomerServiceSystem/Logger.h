#pragma once
#include <mutex>
#include <chrono>

class ServiceLogger final
{
	inline static std::mutex log_mutex{};
public:
	ServiceLogger() = delete;

	static void log(std::ostream& out, const std::string& message);
};