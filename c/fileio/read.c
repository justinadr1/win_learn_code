#include <string.h> 
#include <stdlib.h>
#include <stdio.h>


char* read_file(const char* filename)
{
    FILE* f = fopen(filename, "rb");
    
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* buffer = malloc(size + 1);
    
    fread(buffer, 1, size, f);
    buffer[size] = '\0';

    fclose(f);
    return buffer;
}

void read(char* path)
{
    FILE* file;
    
    file = fopen(path, "r");

    if (file != NULL)       
    {
        char buffer[32];
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            printf(buffer);
        }
        fclose(file);
    } 
}

int main()
{
    char* msg =   read_file("passwd.txt");

    printf(msg);
    
    free(msg);
}
