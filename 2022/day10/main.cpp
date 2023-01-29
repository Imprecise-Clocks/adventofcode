#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"

#define NOOP_CYCLES 1
#define ADDX_CYCLES 2

void fetch_instruction(std::string& buffer, std::string& instruction, int& value, size_t& needed_cycles)
{
    char delimiter = ' ';
    std::vector<std::string> instructions;
    util::tokenize(buffer, delimiter, instructions);

    instruction = instructions.at(0);
    
    if(instruction == "noop") {
        needed_cycles = NOOP_CYCLES;
    }
    if(instruction == "addx") {
        needed_cycles = ADDX_CYCLES;
        value = std::stoi(instructions.at(1));
    }
}

size_t part1()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer; 
    size_t sum = 0;

    size_t cycle_count = 0;
    int registervalue = 1;
    std::vector<int> targetvalues;
    size_t prev_cycle_count;
    size_t needed_cycles;

    std::string instruction;
    int value;

    while(std::getline(file, buffer)) {
        fetch_instruction(buffer, instruction, value, needed_cycles);
        
        prev_cycle_count = cycle_count;

        while(cycle_count - prev_cycle_count != needed_cycles) {
            cycle_count++;
            if(cycle_count == 20) targetvalues.push_back(registervalue * cycle_count);
            else if (cycle_count == 60) targetvalues.push_back(registervalue * cycle_count);
            else if (cycle_count == 100) targetvalues.push_back(registervalue * cycle_count);
            else if (cycle_count == 140) targetvalues.push_back(registervalue * cycle_count);
            else if (cycle_count == 180) targetvalues.push_back(registervalue * cycle_count);
            else if (cycle_count == 220) targetvalues.push_back(registervalue * cycle_count);
        }
        if(instruction == "addx") {
            registervalue += value;
        }
    }
    file.close();
    for(auto target : targetvalues) {
        sum += target;
    }
    return sum;
}

std::string part2()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer; 

    size_t cycle_count = 0;
    int registervalue = 1;
    size_t prev_cycle_count;
    size_t needed_cycles;

    std::string instruction;
    int value;

    const size_t resolution = 240;
    const size_t screenwidth = 40;
    std::vector<char> screen(resolution, '.');
    std::string drawn_screen = "";

    while(std::getline(file, buffer)) {
        fetch_instruction(buffer, instruction, value, needed_cycles);
        
        prev_cycle_count = cycle_count;

        while(cycle_count - prev_cycle_count != needed_cycles) {
            char pixel = '.';
            if((int) (cycle_count % screenwidth) == registervalue)          pixel = '#';
            else if((int) (cycle_count % screenwidth) == registervalue + 1) pixel = '#';
            else if((int) (cycle_count % screenwidth) == registervalue - 1) pixel = '#';

            screen.at(cycle_count) = pixel;
            cycle_count++;
        }
        if(instruction == "addx") {
            registervalue += value;
        }
    }
    file.close();
    
    for(size_t i = 0; i < screen.size(); ++i) {
        if(i % 40 == 0) {
            drawn_screen += '\n';
        }
        drawn_screen += screen.at(i);
    }
    return drawn_screen;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
