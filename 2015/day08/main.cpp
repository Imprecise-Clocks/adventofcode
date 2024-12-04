#include <iostream>
#include <fstream>
#include <stdint.h>
#include <regex>
#include "../../utils/util.h"

int32_t total_single_quote_count = 0;
int32_t total_double_back_count = 0;
int32_t total_hex_number_count = 0;

size_t string_size_regex(const std::string& str) {
    std::string temp = str.substr(1, str.length() - 2);
    std::regex double_back("\\\\\\\\"); // (?!(x[0-9a-f]{2}))
    std::regex single_quote("\\\"");
    std::regex hex_special("\\\\x[0-9a-f]{2}");

    auto single_quote_count(std::distance(
        std::sregex_iterator(temp.begin(), temp.end(), single_quote),
        std::sregex_iterator()));
    auto double_back_count(std::distance(
        std::sregex_iterator(temp.begin(), temp.end(), double_back),
        std::sregex_iterator()));
    auto hex_count(std::distance(
        std::sregex_iterator(temp.begin(), temp.end(), hex_special),
        std::sregex_iterator()));

    total_double_back_count += double_back_count;
    total_single_quote_count += single_quote_count;
    total_hex_number_count += hex_count;

    return temp.size() - (single_quote_count + double_back_count + hex_count * 3);
}

size_t part1()
{        
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t memory_size = 0;
    size_t string_size = 0;
    size_t difference = 0;

    while(std::getline(file, buffer)) {
        memory_size = buffer.size();
        string_size = string_size_regex(buffer);
        difference += memory_size - string_size;
    }
    file.close();

    return difference;
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
