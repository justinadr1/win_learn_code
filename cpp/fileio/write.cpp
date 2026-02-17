#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ofstream file("code.bin", std::ios::app);

    file << "out z;\n";

}

