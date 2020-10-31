#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Forward {

	class FORWARD_API Log {
	public:
		static void Init();
		
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log
#define FW_CORE_TRACE(...)	::Forward::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FW_CORE_INFO(...)	::Forward::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FW_CORE_WARN(...)	::Forward::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FW_CORE_ERROR(...)	::Forward::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FW_CORE_FATAL(...)	::Forward::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client log
#define FW_TRACE(...)		::Forward::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FW_INFO(...)		::Forward::Log::GetClientLogger()->info(__VA_ARGS__)
#define FW_WARN(...)		::Forward::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FW_ERROR(...)		::Forward::Log::GetClientLogger()->error(__VA_ARGS__)
#define FW_FATAL(...)		::Forward::Log::GetClientLogger()->critical(__VA_ARGS__)