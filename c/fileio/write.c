#include <stdio.h>

int main()
{
    FILE* file;

    file = fopen("passwords.txt", "w");
    if (file != NULL)
    {
        fprintf(file, "zeluryp\nripmeznak\naiwprtonjcnruad\n");
        fclose(file);
    }   
}

