#include <iostream>
#include <fstream>
#include <string>
#include "../../utils/util.h"

int part1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t area = 0;

    while(std::getline(file, buffer)) {
        std::vector<std::string> dimensions;
        char delimiter = 'x';
        util::tokenize(buffer, delimiter, dimensions);
        size_t length = std::stoi(dimensions.at(0));
        size_t width = std::stoi(dimensions.at(1));
        size_t height = std::stoi(dimensions.at(2));

        area += 2 * (length*width + width*height + height*length);
        area += std::min(length*width, std::min(width*height, height*length));
    }
    return area;
}

int part2()
{    
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t ribbon_length = 0;
    
    while(std::getline(file, buffer)) {
        std::vector<std::string> dimensions;
        char delimiter = 'x';
        util::tokenize(buffer, delimiter, dimensions);
        size_t length = std::stoi(dimensions.at(0));
        size_t width = std::stoi(dimensions.at(1));
        size_t height = std::stoi(dimensions.at(2));

        size_t smallest = std::min(length, std::min(width, height));
        size_t biggest = std::max(length, std::max(width, height));
        size_t second_smallest = length + width + height - biggest - smallest;
        
        ribbon_length += 2 * (smallest + second_smallest);
        ribbon_length += length * width * height;
    }
    return ribbon_length;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}