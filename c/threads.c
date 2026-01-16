#include <windows.h>
#include <stdio.h>

DWORD WINAPI WorkerThread(LPVOID param) 
{
    (void)param;

    printf("Worker Thread Running...\n");

    return 0;
}

int main(void) 
{
    HANDLE thread;

    printf("Main Thread Starting\n");

    thread = CreateThread(NULL, 0, WorkerThread, NULL, 0, NULL);

    WaitForSingleObject(thread, INFINITE);

    CloseHandle(thread);
    printf("Worker Thread Finished\n");


    return 0;
}
