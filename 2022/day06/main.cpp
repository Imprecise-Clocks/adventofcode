#include <iostream>
#include <fstream>
#include <string>
#include "../../utils/util.h"

size_t part1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t result = 4;

    while(std::getline(file, buffer)) {
        for(size_t i = 0; i < buffer.size(); ++i) {
            if(util::is_unique(buffer.substr(i, result))) {
                result += i;
                break;
            }
        }
    }
    file.close();

    return result;
}

size_t part2()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t result = 14;

    while(std::getline(file, buffer)) {
        for(size_t i = 0; i < buffer.size(); ++i) {
            if(util::is_unique(buffer.substr(i, result))) {
                result += i;
                break;
            }
        }
    }
    file.close();

    return result;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
