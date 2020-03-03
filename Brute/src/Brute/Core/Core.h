#pragma once

#include <memory>

#ifdef BT_PLATFORM_WINDOWS
	#if BT_DYNAMIC_LINK
		#ifdef BT_BUILD_DLL
			#define BRUTE_API __declspec(dllexport)
		#else
			#define BRUTE_API __declspec(dllimport)
		#endif
	#else
		#define BRUTE_API
	#endif
#else
	#error Brute only supports Windows!
#endif

#ifdef BT_DEBUG
	#define BT_ENABLE_ASSERTS
#endif

#ifdef BT_ENABLE_ASSERTS
	#define BT_ASSERT(x, ...) { if(!(x)) { BT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define BT_CORE_ASSERT(x, ...) { if(!(x)) { BT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define BT_ASSERT(x, ...)
	#define BT_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Brute {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	// Future holds:
	/*
	template<typename T>
	class Scope {

	};
	*/

	template<typename T>
	using Ref = std::shared_ptr<T>;
}