#include <iostream>
#include <fstream>
#include <string>
#include "../../utils/md5.h"

int part1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t seed = 0;
    std::string hash = "aaaabbbbccccddddeeeeffff00001111";
    const size_t N_ZEROS = 5;

    std::getline(file, buffer);
    while(hash.substr(0, N_ZEROS) != std::string(N_ZEROS, '0')) {
        hash = md5(buffer + std::to_string(++seed));
    }
    return seed;
}

int part2()
{    
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t seed = 0;
    std::string hash = "aaaabbbbccccddddeeeeffff00001111";
    const size_t N_ZEROS = 6;

    std::getline(file, buffer);
    while(hash.substr(0, N_ZEROS) != std::string(N_ZEROS, '0')) {
        hash = md5(buffer + std::to_string(++seed));
    }
    return seed;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}