#pragma once

#ifdef DIZZY_PLATFORM_WINDOWS
	#ifdef DIZZY_BUILD_DLL
		#define DIZZY_API __declspec(dllexport)
	#else
		#define DIZZY_API __declspec(dllimport)
	#endif
#endif

#ifdef DIZZY_ENABLE_ASSERTS
	#define DIZZY_ASSERT(x, ...) { if(!(x)) { DIZZY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define DIZZY_CORE_ASSERT(x, ...) { if(!(x)) { DIZZY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define DIZZY_ASSERT(x, ...)
	#define DIZZY_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
