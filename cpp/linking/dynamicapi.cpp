#define DYNAMICAPI_EXPORTS
#include "dynamicapi.h"
#include <windows.h>

void _dynamicFunction(const char* message)
{
    MessageBoxA(NULL, message, "My dynamic app", MB_OK);
}
