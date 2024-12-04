#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdint.h>
#include <vector>
#include <map>

#include "../../utils/util.h"

int part1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;

    std::vector<int> left;
    std::vector<int> right;

    std::vector<std::string> tokens;

    while(std::getline(file, buffer)) {
        util::tokenize(buffer, ' ', tokens);
        left.push_back(std::stoi(tokens.at(0)));
        right.push_back(std::stoi(tokens.at(1)));
        tokens.clear();
    }

    file.close();

    int delta = 0;
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    for(int i = 0; i < left.size(); i++) {
        delta += std::abs(left.at(i) - right.at(i));
    }

    return delta;
}

int part2()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;

    std::vector<int> left;
    std::vector<int> right;
    std::map<int, int> hashmappu;

    std::vector<std::string> tokens;

    while(std::getline(file, buffer)) {
        util::tokenize(buffer, ' ', tokens);
        left.push_back(std::stoi(tokens.at(0)));
        right.push_back(std::stoi(tokens.at(1)));
        tokens.clear();
    }

    file.close();

    int result = 0;
    for(int i = 0; i < left.size(); i++) {
        hashmappu[left.at(i)] = 0;
    }
    for(int i = 0; i < right.size(); i++) {
        if(hashmappu.find(right.at(i)) != hashmappu.end()) {
            hashmappu[right.at(i)]++;
        }
    }
    for(const auto &pairs : hashmappu) {
        result += pairs.first * pairs.second;
    }

    return result;
}

int main()
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
