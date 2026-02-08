#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>

int main(void)
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char cmdline[] = "main.exe justin";

    BOOL ok = CreateProcessA(NULL, cmdline, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

    if (!ok) 
    {
        printf("CreateProcess failed (%lu)\n", GetLastError());
        return 1;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
