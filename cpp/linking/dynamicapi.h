#pragma once

#ifdef DYNAMICAPI_EXPORTS
#define DYNAMICAPI_API __declspec(dllexport)
#else
#define DYNAMICAPI_API __declspec(dllimport)
#endif

DYNAMICAPI_API void _dynamicFunction(const char* message);
 