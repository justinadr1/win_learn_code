#include <windows.h>
#include <stdio.h>

void WorkerThread() 
{
    printf("worker thread id: %d\n", GetCurrentThreadId());
}

int main(void) 
{
    HANDLE thread;

    printf("main thread id: %d\n", GetCurrentThreadId());

    thread = CreateThread(NULL, 0, WorkerThread, NULL, 0, NULL);

    WaitForSingleObject(thread, INFINITE);
    
    CloseHandle(thread);

    return 0;
}
