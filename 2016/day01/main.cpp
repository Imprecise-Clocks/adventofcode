#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "../../utils/util.h"

// Hash function for std::array<int, 2>
struct ArrayHash {
	size_t operator()(const std::array<int, 2>& arr) const {
		size_t hash1 = std::hash<int>()(arr[0]);
		size_t hash2 = std::hash<int>()(arr[1]);
		return hash1 ^ (hash2 << 1); // Combine the hashes
	}
};

int part1()
{
	std::ifstream file;
	file.open("input.txt");
	std::string buffer;
	std::getline(file, buffer);
	file.close();

	std::vector<std::string> instructions;
	std::array<int, 4> position = {0, 0, 0, 0};
	util::tokenize(buffer, ',', instructions);
	int current_direction = 0;
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
		int walk = std::stoi(direction.substr(1, direction.size() - 1));
		position[current_direction] += walk;
	}
	int distance = (int) std::max(position.at(0), position.at(2)) - (int) std::min(position.at(0), position.at(2));
	distance += (int) std::max(position.at(1), position.at(3)) - (int) std::min(position.at(1), position.at(3));

	return distance;
}

int part2()
{    
	std::ifstream file;
	file.open("input.txt");
	std::string buffer;
	std::getline(file, buffer);
	file.close();

	std::vector<std::string> instructions;
	std::array<int, 2> position = {0, 0};
	std::unordered_map<std::array<int, 2>, int, ArrayHash> locations;
	int current_direction = 0;

	locations[position] = 1; // Add starting position to visited locations

	util::tokenize(buffer, ',', instructions);
	for(std::string& element: instructions) {
		// remove leading white spaces
		if (element[0] == ' ') {
			element = element.substr(1, element.size() -1);
		}
	}
	for(std::string& direction : instructions) {
		if(direction[0] == 'R') {
			current_direction = (current_direction + 1) % 4;
		}
		if(direction[0] == 'L') {
			current_direction = (current_direction + 3) % 4;
		}
		int gradient = 1;
		bool negative_gradient = false;
		if(current_direction > 1) {
			current_direction -= 2;
			gradient = -1;
			negative_gradient = true;
		}
		int walk = std::stoi(direction.substr(1, direction.size() - 1));
		while(walk--) {
			position[current_direction] += gradient;
			locations[position]++;
			if(locations[position] == 2) {
				return std::abs(position[0]) + std::abs(position[1]);
			}
		}
		if(negative_gradient) {
			current_direction += 2;
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
