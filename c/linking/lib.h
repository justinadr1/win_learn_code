

#ifndef LIB_H
#define LIB_H

#ifdef LIB_EXPORTS
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif

LIB_API int add(int a, int b);

#endif