#include <windows.h>
#include <stdio.h>

DWORD WINAPI worker_thread(LPVOID param) 
{
    (void)param;  // unused parameter

    printf("Worker thread: running\n");
    Sleep(2500);
    printf("Worker thread: done\n");

    return 0;
}

int main(void) {
    HANDLE thread;

    printf("Main thread: starting worker\n");

    thread = CreateThread(NULL, 0, worker_thread, NULL, 0, NULL);

    if (thread == NULL) 
    {
        printf("CreateThread failed (%lu)\n", GetLastError());
        return 1;
    }

    printf("Main thread: waiting\n");
    WaitForSingleObject(thread, INFINITE);

    CloseHandle(thread);

    printf("Main thread: exiting\n");
    return 0;
}
