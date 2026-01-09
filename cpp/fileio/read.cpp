#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

std::string readFile(const std::string& path)
{
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file)
        return "";

    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}


int main()
{
    std::string lyrics = readFile("lyrics.txt");

    std::cout << lyrics;
}