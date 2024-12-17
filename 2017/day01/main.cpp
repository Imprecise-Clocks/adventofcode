#include <iostream>
#include <fstream>
#include <vector>

int part1()
{   
    std::ifstream file;
	file.open("input.txt");
	std::string buffer;
	std::getline(file, buffer);
	file.close();

    int sum = 0;
    std::vector<int> digits;
    for(int i = 0; i < (int) buffer.size() - 1; ++i) {
        if(buffer[i] == buffer[i + 1]) {
            digits.push_back(buffer[i] - 48); // convert char to int
        }
    }
    if(buffer[0] == buffer.back()) {
        digits.push_back(buffer[0] - 48); // convert char to int
    }
    for(int value : digits) {
        sum += value;
    }
    return sum;
}

int part2()
{
    std::ifstream file;
	file.open("input.txt");
	std::string buffer;
	std::getline(file, buffer);
	file.close();

    int sum = 0;
    int offset = (int) buffer.size() / 2;
    std::vector<int> digits;
    for(int i = 0; i < (int) buffer.size(); ++i) {
        int comp_index = (i + offset) % buffer.size();
        if(buffer[i] == buffer[comp_index]) {
            digits.push_back(buffer[i] - 48); // convert char to int
        }
    }
    for(int value : digits) {
        sum += value;
    }
    return sum;
}

int main()
{
    std::cout << "Answer Part 1: " << part1() << "\n";
    std::cout << "Answer Part 2: " << part2() << "\n";
    return 0;
}
