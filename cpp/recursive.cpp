#include <iostream>

void fib(int a, int b, int i)
{
    if (i == 11)
        return;
    std::cout << a << std::endl;
    fib(b, a + b, ++i);
}

int main()
{
    fib(0, 1, 0);
}