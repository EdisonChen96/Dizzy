#include "dzpch.h"
#include "Logger.h"

namespace Dizzy
{
	std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;

	void Logger::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$ ");
		s_CoreLogger = spdlog::stdout_color_mt("Dizzy");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("App");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	// std::shared_ptr<spdlog::logger> Logger::GetCoreLogger()
	// {
	// 	return s_CoreLogger;
	// }
	//
	// std::shared_ptr<spdlog::logger> Logger::GetClientLogger()
	// {
	// 	return s_ClientLogger;
	// }
}
