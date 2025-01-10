#pragma once
#include "Dizzy/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Dizzy
{
    class DIZZY_API Logger
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define DIZZY_CORE_INFO(...)      ::Dizzy::Logger::GetCoreLogger()->info(__VA_ARGS__);
#define DIZZY_CORE_WARN(...)      ::Dizzy::Logger::GetCoreLogger()->warn(__VA_ARGS__);
#define DIZZY_CORE_ERROR(...)     ::Dizzy::Logger::GetCoreLogger()->error(__VA_ARGS__);
#define DIZZY_CORE_TRACE(...)     ::Dizzy::Logger::GetCoreLogger()->trace(__VA_ARGS__);
#define DIZZY_CORE_FATAL(...)     ::Dizzy::Logger::GetCoreLogger()->fatal(__VA_ARGS__);

// Client log macros
#define DIZZY_INFO(...)           ::Dizzy::Logger::GetClientLogger()->info(__VA_ARGS__);
#define DIZZY_WARN(...)           ::Dizzy::Logger::GetClientLogger()->warn(__VA_ARGS__);
#define DIZZY_ERROR(...)          ::Dizzy::Logger::GetClientLogger()->error(__VA_ARGS__);
#define DIZZY_TRACE(...)          ::Dizzy::Logger::GetClientLogger()->trace(__VA_ARGS__);
#define DIZZY_FATAL(...)          ::Dizzy::Logger::GetClientLogger()->fatal(__VA_ARGS__);
