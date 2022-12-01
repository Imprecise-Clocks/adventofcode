#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int part1()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer;
    size_t max = 0;
    size_t sum = 0;

    while(std::getline(file, buffer)) {

        if(buffer.size() == 0) {
            if(max < sum) {
                max = sum;
            }        
            sum = 0;
            continue;
        }
        sum += std::stoi(buffer);
    }
    return max;
}

int part2()
{
    std::ifstream file;
    file.open("input2.txt");
    std::string buffer;
    std::vector<size_t> snacks;
    size_t sum = 0;

    while(std::getline(file, buffer)) {

        if(buffer.size() == 0) {
            snacks.push_back(sum);   
            sum = 0;
            continue;
        }
        sum += std::stoi(buffer);
    }
    std::sort(snacks.begin(), snacks.end(), [](size_t a, size_t b) {
        return a > b;
    });

    return snacks.at(0) + snacks.at(1) + snacks.at(2);
}

int main(int argc, char** argv) 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}