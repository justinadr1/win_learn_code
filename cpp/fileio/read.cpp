#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream file("code.bin");

    std::string content(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    std::cout << content;

}
