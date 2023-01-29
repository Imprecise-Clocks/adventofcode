#include <iostream>
#include <fstream>
#include <string>

int part1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    int floor = 0;

    std::getline(file, buffer);
    file.close();

    for(char direction : buffer) {
        if(direction == '(') ++floor;
        else --floor;
    }
    return floor;
}

int part2()
{    
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    int floor = 0;

    std::getline(file, buffer);
    file.close();
    
    for(size_t i = 0; i < buffer.size(); ++i) {
        if(buffer.at(i) == '(') ++floor;
        else --floor;
        if(floor == -1) {
            return i + 1;
        }
    }
    return -1;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}