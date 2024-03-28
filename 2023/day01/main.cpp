#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <stdint.h>

uint64_t create_number_mask(const std::string& input) {
    uint64_t mask = 0;
    for(auto character : input) {
        mask = mask << 8;
        mask |= character;
    }
    return mask;
}

int part1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    std::vector<int> digits = {};
    int sum = 0;
    int digit;

    while(std::getline(file, buffer)) {
        for(size_t i = 0; i < buffer.size(); ++i) {
            if(buffer[i] >= '0' && buffer[i] <= '9') {
                digit = 10 * ((int) buffer[i] - (int) '0');
                break;
            }
        }
        for(int i = buffer.size(); i >= 0; --i) {
            if(buffer[i] >= '0' && buffer[i] <= '9') {
                digit += (int) buffer[i] - (int) '0';
                break;
            }
        }
        digits.push_back(digit);
    }
    file.close();

    for(int digit : digits) {
        sum += digit;
    }
    return sum;
}

int part2()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    std::vector<int> digits = {};
    std::array<std::string, 10> written_digits = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}; 
    int sum = 0;
    int digit = -1;
    bool digit_found = false;

    std::vector<uint64_t> digit_masks;
    for(const auto& _digit : written_digits) {
        digit_masks.push_back(create_number_mask(_digit));
    } 

    while(std::getline(file, buffer)) {        
        for(size_t i = 0; i < buffer.size(); ++i) {
            if(buffer[i] >= '0' && buffer[i] <= '9') {
                digit = (int) (buffer[i] - '0');
                digit *= 10;
                break;
            }
  
            for(int j = 3; j <= 5; ++j) {
                if(i + j >= buffer.size()) break;
                uint64_t slice_mask = create_number_mask(buffer.substr(i, j));
                for(size_t k = 0; k < digit_masks.size(); ++k) {
                    if(digit_masks[k] == slice_mask) {
                        digit = k;
                    }
                }
            }
            if(digit != -1) {
                digit *= 10;
                break;
            }
        }
        
        for(int i = buffer.size() - 1; i >= 0; --i) {
            if(buffer[i] >= '0' && buffer[i] <= '9') {
                digit += (int) (buffer[i] - '0');
                break;
            }
            for(int j = 3; j <= 5; ++j) {
                if(i - j < 0) break;
                uint64_t slice_mask = create_number_mask(buffer.substr(i - j + 1, j));
                for(size_t k = 0; k < digit_masks.size(); ++k) {
                    if(digit_masks[k] == slice_mask) {
                        digit += k;
                        digit_found = true;
                        break;
                    }
                }
                if(digit_found) {
                    break;
                }
            }
            if(digit_found) {
                break;
            }
        }

        digits.push_back(digit);
        digit = -1;
        digit_found = false;
    }
    file.close();

    for(int digit : digits) {
        sum += digit;
    }
    return sum;
}

int main()
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
