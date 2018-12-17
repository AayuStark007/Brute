#pragma once

#ifdef BT_PLATFORM_WINDOWS
	#ifdef BT_BUILD_DLL
		#define BRUTE_API __declspec(dllexport)
	#else
		#define BRUTE_API __declspec(dllimport)
	#endif
#else
	#error Brute only supports Windows!
#endif

#define BIT(x) (1 << x)