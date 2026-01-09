#pragma once

#ifdef LIB_EXPORTS
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif

extern "C" LIB_API int add(int a, int b);