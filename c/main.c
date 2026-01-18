#include <stdio.h>
#include <string.h>
#include <windows.h>

int main()
{
    FILE* file = fopen("lyrics.txt", "r");

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    char* buffer = malloc(size + 1);
    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    printf("%p\n", file);

    fclose(file);
    free(buffer);
}