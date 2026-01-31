#include <iostream>

struct Address
{
    int octets[4];

    int& operator[](int i)
    {
        return octets[i];
    }

    void print()
    {
        for (int i = 0; i < 3; i++)
            std::cout << octets[i] << '.';
        std::cout << octets[3] << std::endl;
    }
};

int main()
{
    Address address;

    

}