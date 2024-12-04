#include <cstdint>
#include <array>
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
	std::array<int32_t, 4> position = {0, 0, 0, 0};
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
			position[current_direction] += walk;
		}
		if(direction[0] == 'L') {
			current_direction = (current_direction - 1 == -1) ? 3 : current_direction - 1;
			int32_t walk = std::stoi(direction.substr(1, direction.size() - 1));
			position[current_direction] += walk;
		}
	}
	int32_t distance = (int32_t) std::max(position.at(0), position.at(2)) - (int32_t) std::min(position.at(0), position.at(2));
	distance += (int32_t) std::max(position.at(1), position.at(3)) - (int32_t) std::min(position.at(1), position.at(3));
	return distance;
}

int32_t part2()
{    
	std::ifstream file;
	file.open("input.txt");
	std::string buffer;
	std::getline(file, buffer);
	file.close();

	std::vector<std::string> instructions;
	std::array<int32_t, 2> position = {0, 0};
	util::tokenize(buffer, ',', instructions);
	int32_t current_direction = 0;
	for(std::string& element: instructions) {
		// remove leading white spaces
		if (element[0] == ' ')
			element = element.substr(1, element.size() -1);
	}

	int32_t gradient;
	std::vector<std::array<int32_t, 2>> positions = {};
	for(std::string& direction: instructions) {
		positions.push_back(position);
		if(direction[0] == 'R') {
			current_direction = (current_direction + 1) % 4;
			if(current_direction == 0 || current_direction == 2) {
				gradient = (current_direction == 0) ? 1 : -1; 
				current_direction = 0;
			}
			else {
				gradient = (current_direction == 1) ? 1 : -1; 
				current_direction = 1;
			}
			int32_t walk = std::stoi(direction.substr(1, direction.size() - 1));
			position[current_direction] += walk * gradient;
		}
		if(direction[0] == 'L') {
			current_direction = (current_direction - 1 == -1) ? 3 : current_direction - 1;
			if(current_direction == 0 || current_direction == 2) {
				gradient = (current_direction == 0) ? 1 : -1; 
				current_direction = 0;
			}
			else {
				gradient = (current_direction == 1) ? 1 : -1; 
				current_direction = 1;
			}
			int32_t walk = std::stoi(direction.substr(1, direction.size() - 1));
			position[current_direction] += walk * gradient;
		}
		for(auto& p : positions) {
			if(position[0] == p[0] && position[1] == p[1]) {
				return position[0] + position[1];
			}
		}
	}
	return -1;
}

int main(int argc, char** argv) 
{
	std::cout << "The answer to part 1: " << part1() << std::endl;
	std::cout << "The answer to part 2: " << part2() << std::endl;
	return 0;
}
