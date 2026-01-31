#include <windows.h>
#include <stdio.h>

int main() 
{
    HANDLE hFile;
    const char* filename = "code.bin";
    
    // create or overwrite file
    hFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) 
    {
        printf("Failed to create file. Error: %lu\n", GetLastError());
        return 1;
    }

    printf("File '%s' created successfully.\n", filename);

    CloseHandle(hFile); 
    return 0;
}
