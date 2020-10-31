#pragma once

#ifdef FW_PLATFORM_WINDOWS
	#ifdef FW_BUILD_DLL 
		#define FORWARD_API _declspec(dllexport)
	#else
		#define FORWARD_API _declspec(dllimport)
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