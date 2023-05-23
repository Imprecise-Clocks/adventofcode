#include <iostream>
#include <fstream>
#include <stdint.h>
#include <regex>
#include "../../utils/util.h"


size_t strSize(const std::string& str) {
    std::string temp = str.substr(1, str.length() - 2);
    std::regex double_back("\\\\\\\\(?!(x[0-9|a-f][0-9|a-f]))");
    std::regex single_quote("\\\"");
    std::regex hex_special("\\\\[x][0-9|a-f][0-9|a-f]");

    auto single_quote_count(std::distance(
        std::sregex_iterator(temp.begin(), temp.end(), single_quote),
        std::sregex_iterator()));
    auto double_back_count(std::distance(
        std::sregex_iterator(temp.begin(), temp.end(), double_back),
        std::sregex_iterator()));
    auto hex_count(std::distance(
        std::sregex_iterator(temp.begin(), temp.end(), hex_special),
        std::sregex_iterator()));

    return str.length() - single_quote_count - double_back_count - hex_count * 3 - 2;
}

size_t part1()
{        
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t sum = 0;
    size_t memory_size; 
    size_t string_size; 

    while(std::getline(file, buffer)) {
        memory_size = buffer.size();
        string_size = strSize(buffer);
        sum += memory_size - string_size;
    }
    file.close();
    
    return sum;
}

size_t part2()
{  
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    while(std::getline(file, buffer)) {
    }
    file.close();
    
    return 0;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
