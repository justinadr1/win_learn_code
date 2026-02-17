#include <stdio.h>

int main()
{
    FILE* file = fopen("code.bin", "a");
    
    fprintf(file, "out z;\n");
    fclose(file);
    
}

