#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
    
// pointer arithmetic practice
int main(void)
{   
    int buffer[3] = { 0xAA, 0xBB, 0xCC };

    int x = 0x44556677;

    printf("%p: %X\n", &x, x);

    printf("%p: %X\n", (char*)&x, *((unsigned char*)&x));

    printf("%p: %X\n", buffer, *(buffer));
    printf("%p: %X\n", buffer + 1, *(buffer + 1));
    printf("%p: %X\n", buffer + 2, *(buffer + 2));
    
    printf("%p: %X\n", buffer - 2, *(buffer - 2));
}   