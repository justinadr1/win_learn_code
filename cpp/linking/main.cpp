#include <iostream>
#include <string>
#include "dynamicapi.h"


int main(int argc, char* argv[])
{
    std::cout << "your message: ";
    
    std::string message;

    std::cin >> message;

    _dynamicFunction(message.c_str());

    return 0;
}
