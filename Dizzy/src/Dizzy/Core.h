#pragma once

#ifdef DIZZY_PLATFORM_WINDOWS
	#ifdef DIZZY_BUILD_DLL
		#define DIZZY_API __declspec(dllexport)
	#else
		#define DIZZY_API __declspec(dllimport)
	#endif
#endif

#define BIT(x) (1 << x)
