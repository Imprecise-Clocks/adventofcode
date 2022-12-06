#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

bool is_unique(const std::string& string)
{
    std::set<char> characters;
    for(char c : string) {
        characters.insert(c);
    }
    return characters.size() == string.size();
}

size_t part1()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer;
    size_t result = 4;

    while(std::getline(file, buffer)) {
        for(size_t i = 0; i < buffer.size(); ++i) {
            if(is_unique(buffer.substr(i, result))) {
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
    file.open("input1.txt");
    std::string buffer;
    size_t result = 14;

    while(std::getline(file, buffer)) {
        for(size_t i = 0; i < buffer.size(); ++i) {
            if(is_unique(buffer.substr(i, result))) {
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
