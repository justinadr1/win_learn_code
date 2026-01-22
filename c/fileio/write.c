#include <stdio.h>

int main()
{
    FILE* file;

    file = fopen("crypt.txt", "w");
    if (file != NULL)
    {
        fprintf(file, "d914c7a0e18f3\n");
        fclose(file);
    }   
}

