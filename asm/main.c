#include <stdio.h>

int main()
{
    int n = 10;
    int a = 0;
    int b = 1;

    for (int i = 0; i < n; i++)
    {
        int t = a + b;
        a = b;
        b = t;
        printf("%d ", a);
    }
    

}