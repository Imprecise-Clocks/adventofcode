#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

size_t char2priority(char character)
{
    if(character >= 'A' && character <= 'Z') return 26 + character - 'A' + 1;
    if(character >= 'a' && character <= 'z') return character - 'a' + 1;
    return 0;
}

int part1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t sum = 0;

    while(std::getline(file, buffer)) {
        std::string temp = buffer.substr(0, (size_t)buffer.size()/2);
        std::vector<char> first_backbag(temp.begin(),temp.end());

        temp = buffer.substr((size_t)buffer.size()/2);
        std::vector<char> second_backbag(temp.begin(),temp.end());

        std::vector<char> intersection;

        std::sort(first_backbag.begin(), first_backbag.end(), [](char a, char b){
            return a < b;
        });
        std::sort(second_backbag.begin(), second_backbag.end(), [](char a, char b){
            return a < b;
        });
        std::set_intersection(first_backbag.begin(), first_backbag.end(),second_backbag.begin(), second_backbag.end(), std::back_inserter(intersection));

        sum += char2priority(intersection.at(0));
    }
    file.close();
    
    return sum;
}

int part2()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t sum = 0;
    std::vector<std::string> group = {};

    while(std::getline(file, buffer)) {
        group.push_back(buffer);
        if(group.size() == 3) {
            std::vector<char> first_elf(group.at(0).begin(), group.at(0).end());
            std::vector<char> second_elf(group.at(1).begin(), group.at(1).end());
            std::vector<char> third_elf(group.at(2).begin(), group.at(2).end());

            std::sort(first_elf.begin(), first_elf.end(), [](char a, char b){
                return a < b;
            });
            std::sort(second_elf.begin(), second_elf.end(), [](char a, char b){
                return a < b;
            });
            std::sort(third_elf.begin(), third_elf.end(), [](char a, char b){
                return a < b;
            });

            std::vector<char> first_intersection;
            std::vector<char> second_intersection;
            std::set_intersection(first_elf.begin(), first_elf.end(),second_elf.begin(), second_elf.end(), std::back_inserter(first_intersection));
            std::set_intersection(first_intersection.begin(), first_intersection.end(),third_elf.begin(), third_elf.end(), std::back_inserter(second_intersection));
            
            sum += char2priority(second_intersection.at(0));
            group.clear();
        }
    }
    file.close();

    return sum;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
