#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdint.h>
#include <vector>

#include "../../utils/util.h"

bool is_increasing(const std::vector<int>& vec, int max_diff, int min_diff) {
    for(size_t i = 0; i < vec.size() - 1; ++i) {
        if(vec.at(i) > vec.at(i + 1) || vec.at(i + 1) - vec.at(i) > max_diff || vec.at(i + 1) - vec.at(i) < min_diff) {
            return false;
        } 
    }
    return true;
}

int part1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    std::vector<int> tokens;
    std::vector<int> reverse;
    int safe_count = 0;

    while(std::getline(file, buffer)) {
        util::tokenize(buffer, ' ', tokens);
        std::reverse_copy(std::begin(tokens), std::end(tokens), std::begin(reverse));
        if(is_increasing(tokens, 3, 1) || is_increasing(reverse, 3, 1)) {
            safe_count++;
        }
        tokens.clear();
        reverse.clear();
    }
    file.close();

    return safe_count;
}

int part2()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    std::vector<int> tokens;
    std::vector<int> reverse;
    int safe_count = 0;

    while(std::getline(file, buffer)) {
        util::tokenize(buffer, ' ', tokens);
        std::reverse_copy(std::begin(tokens), std::end(tokens), std::end(reverse));
        if(is_increasing(tokens, 3, 1) || is_increasing(reverse, 3, 1)) {
            safe_count++;
        }
        else {
            for (size_t i = 0; i < tokens.size(); ++i) {
                reverse.clear();

                std::vector<int> reduced_tokens = tokens;
                reduced_tokens.erase(reduced_tokens.begin() + i);
                std::reverse_copy(std::begin(reduced_tokens), std::end(reduced_tokens), std::begin(reverse));
                if(is_increasing(reduced_tokens, 3, 1) || is_increasing(reverse, 3, 1)) {
                    safe_count++;
                    break;
                }
            }
        }
        tokens.clear();
        reverse.clear();
    }

    file.close();
    return safe_count;
}

int main()
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
