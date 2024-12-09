#include <cstdint>
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "../../utils/util.h"

// Hash function for std::array<int32_t, 2>
struct ArrayHash {
    std::size_t operator()(const std::array<int32_t, 2>& arr) const {
        std::size_t seed = 0;
        for (const auto& elem : arr) {
            seed ^= std::hash<int32_t>()(elem) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

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
		}
		if(direction[0] == 'L') {
			current_direction = (current_direction + 3) % 4;
		}
		int32_t walk = std::stoi(direction.substr(1, direction.size() - 1));
		position[current_direction] += walk;
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
	std::unordered_map<std::array<int32_t, 2>, int32_t, ArrayHash> locations;
	int32_t current_direction = 0;

	util::tokenize(buffer, ',', instructions);
	for(std::string& element: instructions) {
		// remove leading white spaces
		if (element[0] == ' ')
			element = element.substr(1, element.size() -1);
	}
	for(std::string& direction : instructions) {
		if(direction[0] == 'R') {
			current_direction = (current_direction + 1) % 4;
		}
		if(direction[0] == 'L') {
			current_direction = (current_direction + 3) % 4;
		}
		int32_t gradient = 1;
		if(current_direction > 1) {
			current_direction -= 2;
			gradient = -1;
		}
		int32_t walk = std::stoi(direction.substr(1, direction.size() - 1));
		while(walk--) {
			position[current_direction] += gradient;
			locations[position]++;
			if(locations[position] == 2) {
				int32_t distance = std::abs(position[0]) + std::abs(position[1]);
				return distance;
			}
		}
	}
	return -1;
}

int main() 
{
	std::cout << "The answer to part 1: " << part1() << std::endl;
	std::cout << "The answer to part 2: " << part2() << std::endl;
	return 0;
}
