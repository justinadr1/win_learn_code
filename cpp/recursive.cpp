#include <iostream>

void fun(int a)
{
    int i = a;

    if (i > 0)
    {
        fun(--i);
        std::cout << i << std::endl;
    }
}

int main()
{
    fun(5);
}