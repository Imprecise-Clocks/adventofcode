#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include "../../utils/util.h"

int32_t part1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
	std::getline(file, buffer);
    file.close();

	std::vector<std::string> instructions;
	std::vector<int32_t> directions = {0, 0, 0, 0};
	util::tokenize(buffer, ',', instructions);
	int32_t current_direction = 0;
	for(std::string& element: instructions) {
		if (element[0] == ' ')
			element = element.substr(1, element.size() -1);
	}

    for(std::string& direction : instructions) {
   		if(direction[0] == 'R') {
			current_direction = (current_direction + 1) % 4;
			int32_t walk = std::stoi(direction.substr(1, direction.size() - 1));
			directions[current_direction] += walk;
		}
   		if(direction[0] == 'L') {
			current_direction = (current_direction - 1) % 4;
			int32_t walk = std::stoi(direction.substr(1, direction.size() - 1));
			directions[current_direction] += walk;
		}
    }
	int32_t distance = std::max(directions.at(0), directions.at(2)) - std::min(directions.at(0), directions.at(2));
	distance += std::max(directions.at(1), directions.at(3)) - std::min(directions.at(1), directions.at(3));
    return distance;
}

int32_t part2()
{    
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    std::getline(file, buffer);
    file.close();
	
	return -1;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
