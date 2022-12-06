#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../utils/util.h"

size_t get_stack_index(size_t n)
{
    return (size_t) (n / 4);
}

void load_stack(std::vector<std::vector<char>>& stack, std::ifstream& file)
{
    std::string buffer;
    size_t stacksize = 8;

    stack.resize(9);
    while(stacksize--) {
        std::getline(file, buffer);
        for(size_t i = 1; i < 34; i+=4) {
            char temp = buffer.at(i);
            if(temp >= 'A' && temp <= 'Z') {
                size_t stackidx = get_stack_index(i);
                stack.at(stackidx).insert(stack.at(stackidx).begin(), 1, temp);
            }
        }
    }
    // skip unnecessary lines
    std::getline(file, buffer);
    std::getline(file, buffer);
}

std::string part1()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer;
    std::string result;
    std::vector<std::vector<char>> stacks;
    load_stack(stacks, file);

    while(std::getline(file, buffer)) {
        std::vector<std::string> instructions;
        char delimiter = ' ';
        util::tokenize(buffer, delimiter, instructions);
        size_t move = std::stoi(instructions.at(1));
        size_t from = std::stoi(instructions.at(3)) - 1;
        size_t to = std::stoi(instructions.at(5)) - 1;

        while(move--) {
            if(stacks.at(from).size() != 0) {
                char temp = stacks.at(from).back();
                stacks.at(from).pop_back();
                stacks.at(to).push_back(temp);
            }
        }
    }
    file.close();

    for(size_t i = 0; i < stacks.size(); ++i) {
        result += stacks.at(i).back();
    }
    return result;
}

std::string part2()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer;
    std::string result;
    std::vector<std::vector<char>> stacks;
    load_stack(stacks, file);

    while(std::getline(file, buffer)) {
        std::vector<std::string> instructions;
        char delimiter = ' ';
        util::tokenize(buffer, delimiter, instructions);
        size_t move = std::stoi(instructions.at(1));
        size_t from = std::stoi(instructions.at(3)) - 1;
        size_t to = std::stoi(instructions.at(5)) - 1;

        std::vector<char> buffer_stack;
        while(move--) {
            if(stacks.at(from).size() != 0) {
                char temp = stacks.at(from).back();
                stacks.at(from).pop_back();
                buffer_stack.push_back(temp);
            }
        }
        while(buffer_stack.size()) {
            char temp = buffer_stack.back();
            buffer_stack.pop_back();
            stacks.at(to).push_back(temp);
        }
    }
    file.close();

    for(size_t i = 0; i < stacks.size(); ++i) {
        result += stacks.at(i).back();
    }
    return result;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
