#include "staticapi.h"
#include <windows.h>

void _staticFunction(const char* message)
{
    MessageBoxA(NULL, message, "My static app", MB_OK);
}
