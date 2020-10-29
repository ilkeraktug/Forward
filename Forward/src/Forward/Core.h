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