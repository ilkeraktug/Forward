#pragma once

#include <memory>

#ifdef FW_PLATFORM_WINDOWS
#if FW_DYNAMIC_LINK
	#ifdef FW_BUILD_DLL 
		#define FORWARD_API __declspec(dllexport)
	#else
		#define FORWARD_API __declspec(dllimport)
	#endif
#else
	#define FORWARD_API
#endif
#else
	#error Only Windows
#endif

#ifdef FW_ENABLE_ASSERT
	#define FW_CORE_ASSERT(x, ...) { if(!(x)) { FW_CORE_ERROR("Assertion Failed : {0}", __VA_ARGS__); __debugbreak(); } }
	#define FW_ASSERT(x, ...) { if(!(x)) { FW_ERROR("Assertion Failed : {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FW_CORE_ASSERT(x, ...)
	#define FW_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define Fw_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Forward {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}