#include <windows.h>
#include <stdio.h>

int main() 
{
    const char* filename = "code.bin";

    if (!DeleteFile(filename)) 
    {
        printf("Failed to delete file '%s'. Error: %lu\n", filename, GetLastError());
        return 1;
    }

    printf("File '%s' deleted successfully.\n", filename);
    return 0;
}
