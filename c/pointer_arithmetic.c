#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
    
// pointer arithmetic practice
int main(void)
{   
    int buffer[3] = { 0xAA, 0xBB, 0xCC };

    int x = 0x44556677;

    // this prints big endian
    printf("%p: %X\n", &x, x);
    // so the first byte here is actually 77 and second byte is 66
    printf("%p: %X\n", (char*)&x + 1, *((unsigned char*)&x + 1));

    printf("%p: %X\n", buffer, *(buffer));
    printf("%p: %X\n", buffer, *(buffer + 1));
    printf("%p: %X\n", buffer, *(buffer + 2));
    
    printf("%p: %X\n", buffer - 2, *(buffer - 2));
}