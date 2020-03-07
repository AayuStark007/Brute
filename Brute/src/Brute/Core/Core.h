#pragma once

#include <memory>

// detect platform using predefined macros
#ifdef _WIN32
	// Windows x64/x86
	#ifdef _WIN64
		// x64
		#define BT_PLATFORM_WINDOWS
	#else
		// x86
		#error "x86 builds are not supported"
	#endif // _WIN64
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS Simulator is not supported"
	#elif TARGET_OS_IPHONE == 1
		#define BT_PLATFORM_IOS
		#error "IOS is not supported"
	#elif TARGET_OS_MAC == 1
		#define BT_PLATFORM_MACOS
		#error "MacOS is not supported"
	#else
		#error "Unknown Apple Platform"
	#endif
#elif defined(__ANDROID__)
	#define BT_PLATFORM_ANDROID
	#error "Android not supported"
#elif defined(__linux__)
	#define BT_PLATFORM_LINUX
	#error "Linux is not supported"
#else
	#error "Unknown platform"
#endif // end of platform detection


// DLL support
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
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	// Future holds:
	/*
	template<typename T>
	class Scope {

	};
	*/

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
