#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* file = fopen("code.bin", "r");
    fseek(file, 0, SEEK_END);  
    size_t size = ftell(file);
    rewind(file);

    char* buffer = malloc(size + 1);
    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    printf(buffer);

    free(buffer);
    fclose(file);
}