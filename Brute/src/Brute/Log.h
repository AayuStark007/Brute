#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Brute {

	class BRUTE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define BT_CORE_TRACE(...)    ::Brute::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BT_CORE_INFO(...)     ::Brute::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BT_CORE_WARN(...)     ::Brute::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BT_CORE_ERROR(...)    ::Brute::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BT_CORE_FATAL(...)    ::Brute::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define BT_TRACE(...)	      ::Brute::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BT_INFO(...)	      ::Brute::Log::GetClientLogger()->info(__VA_ARGS__)
#define BT_WARN(...)	      ::Brute::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BT_ERROR(...)	      ::Brute::Log::GetClientLogger()->error(__VA_ARGS__)
#define BT_FATAL(...)	      ::Brute::Log::GetClientLogger()->critical(__VA_ARGS__)
