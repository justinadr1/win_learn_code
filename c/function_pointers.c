#include <stdio.h>

int addone(int a)
{
    return a + 1;
}

int minusone(int a)
{
    return a - 1;
}

int calc(int (*func)(int), int val)
{
    return func(val);
}


int main()
{   
    printf("%p\n", calc);
    printf("%p\n", addone);
    printf("%p\n", minusone);
    
    printf("%i\n", calc(addone, 5));

    printf("%i\n", calc(minusone, 5));
     
    int (*_addOne)(int) = addone;

    printf("%i\n", _addOne(10));
}